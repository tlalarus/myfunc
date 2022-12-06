#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <random>
#include <algorithm>

#define MIN_DEPTH 3

using namespace std;

template <typename S>
ostream& operator<<(ostream& os, const vector<S>& vector){
	// Printing all the elements
	// using <<
	for(auto element : vector){
		os << element << " ";
	}
	return os;
}

struct Pos{
	int x;
	int y;
	Pos() {};
	Pos(int x_, int y_){
		x = x_;
		y = y_;
	}
};

int n_cnt = 0;
class Node{
	vector<int> path;
	map<int, Node> children;
	bool leaf;
	int depth;
	
	vector<Pos> feature;
	
public:
		Node() {};
	void InsertNode(vector<int>& indice_in_, vector<int>& path_, int concat_idx, int depth_);
	void SearchNode(vector<int>& path_in_, vector<int>& path_out_, vector<Pos>& feature_);
	
};

void Func(vector<Pos>& feat_){
	
	cout << "Gen Feature: ";
	mt19937 mt_rand(n_cnt++);
	uniform_int_distribution<int> range(0, 100);
	
	for(int i=0; i<5; i++){
		int rand_val = range(mt_rand);
		cout << "("<< rand_val << ", " << rand_val+10 << ")  ";
		feat_.emplace_back(rand_val, rand_val+10);
	}
	cout << endl;
}
void Node::InsertNode(vector<int>& indice_in_, vector<int>& path_, int concat_idx, int depth_) {
	
	this->depth = depth_;
	// 현재까지의 경로를 현재 노드에 저장한다.
	copy(path_.begin(), path_.end(), std::back_inserter(path));
	path.push_back(indice_in_[concat_idx]);
	
	string space = "";
	for(int i=0; i<depth_; i++){
		space += " ";
	}
	
	
	cout << space << "Current path: ";
	cout << path << "(" << this->depth << ")" << endl;
	
	// 현재 인덱스번호 다음 인덱스부터 자식노드에 추가한다.
	// 자식노드의 값 자체가 children의 key가 된다.
	for(int i=concat_idx+1; i<indice_in_.size(); i++){
		
		// 현재 자식노드에 존재하는지 검색
		if(children.find(indice_in_[i]) == children.end()){
			cout << space << "insert children: " << indice_in_[i] << endl;
			children.insert({indice_in_[i], Node()});
			children[indice_in_[i]].InsertNode(indice_in_, path, i, depth_+1);
		} else{
			cout << space << "already exist" << endl;
		}
	}
	
	// 최소 노드 수 만족하면 leaf 노드 생
	if(path.size() >= MIN_DEPTH){
		// Polar histogram 생성
		leaf = true;
		
		// 현재 path 출력
		cout << space << "@@ Leaf node path: ";
		cout << path << "(" << this->depth << ")" << endl;
		Func(feature);
	}

}

void Node::SearchNode(vector<int> &path_in_, vector<int> &path_out_, vector<Pos>& feature_) {
	
	if(path_in_.empty()){
		// found
		copy(path.begin(), path.end(), back_inserter(path_out_));
		copy(feature.begin(), feature.end(), back_inserter(feature_));
		
		return;
	}
	
	if(children.find(path_in_.front()) != children.end()) {
		// search next sub path in children
		vector<int> sub_path_;
		int path_len = path_in_.size();
		copy(path_in_.begin()+1, path_in_.end(), back_inserter(sub_path_));
		
		return (children[path_in_.front()].SearchNode(sub_path_, path_out_, feature_));
	}
	
}


// 생성시 : combination(순서고려X)의 feature를 저장한다. ccw ordered permutation list를 생성한다.
// 검색시 : ccw ordered permutation list를 돌면서 feature를 rearrange 한다.
class Combination{
public:
	Node root;
	int base;
	Combination() {};
	Combination(vector<int>& indice_);
	bool Search(vector<int>& path_in_, vector<Pos>& feature_);
};

Combination::Combination(vector<int>& indice_) {
	// sorted indice 입력받음
	base = indice_.front();
	vector<int> path_init;
	root.InsertNode(indice_, path_init, 0, 0);
}

bool Combination::Search(vector<int> &path_in_, vector<Pos>& feature_) {
	if(path_in_[0] !=  base){
		return false;
	}
	
	vector<int> indice_ret;
	vector<int> target;
	copy(path_in_.begin()+1, path_in_.end(), back_inserter(target));
	
	root.SearchNode(target, indice_ret, feature_);
	
	if(indice_ret.empty()){
		return false;
	}
	
	cout << "Return path:" << indice_ret << endl;
	return true;
}

void GetPermList(){

}

int main() {
	// in : (u,v) 좌표들
	// out : ccw 정렬된 (u,v) 좌표 조합들
	vector<Combination> comb_tree;
	int n = 4;
	
	cout << "++ Comb tree Insertion Begin!! (" << n << ") ++" << endl;
	for(int i=0; i<n; i++){
		vector<int> indice;
		indice.push_back(i);
		for(int j=0; j<n; j++){
			if(i != j){
				indice.push_back(j);
			}
		}
		comb_tree.emplace_back(indice);
	}
	cout << "++ Comb tree Insertion End!! ++" << endl << endl << endl;
	
	
	cout << "++ Comb tree Search Begin!! ++" << endl;
	vector<vector<int>> targets;
	targets.push_back({0, 2, 3});
	targets.push_back({1, 3, 0});
	targets.push_back({1, 1, 1});
	targets.push_back({2, 1, 3, 0});
	targets.push_back({1, 0, 3});
	
	vector<vector<Pos>> features;
	for(auto target : targets){
		
		int base_ = target.front();
		vector<int> tmp;
		copy(target.begin(), target.end(), back_inserter(tmp));
		sort(tmp.begin()+1, tmp.end());
		
		cout << "Find " << target << " -> " << tmp << endl;
		
		vector<Pos> tmp_ret;
		if(comb_tree[base_].Search(tmp, tmp_ret)){
			features.push_back(move(tmp_ret));
		} else{
			features.push_back({});
		}
		
	}
	
	int n_out = targets.size();
	for(int i=0; i<n_out; i++){
		cout << "In: " << targets[i] << endl;
		
		cout << "Out: ";
		for(int j=0; j<features[i].size(); j++){
			cout << features[i][j].x << "," << features[i][j].y << "  ";
		}
		cout << endl;
	}
	
	return 0;
}
