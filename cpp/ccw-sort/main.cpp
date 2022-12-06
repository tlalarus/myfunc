#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <random>
#include <algorithm>
#include <chrono>


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

class CombNode{
	vector<int> path;
	map<int, CombNode> children;
	bool leaf;
	int depth;
	
	vector<Pos> feature;
	
public:
		CombNode() {};
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
void CombNode::InsertNode(vector<int>& indice_in_, vector<int>& path_, int concat_idx, int depth_) {
	
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
			children.insert({indice_in_[i], CombNode()});
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

void CombNode::SearchNode(vector<int> &path_in_, vector<int> &path_out_, vector<Pos>& feature_) {
	
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
	CombNode root;
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



#define PERM_TEST
#ifdef PERM_TEST

bool is_promising(){

}

void perms(vector<int>& indice_src_, queue<int>& remains_){
	
	if(is_promising()){
		// indice_src_ 에 요소 하나를 더 추가한다.
		
	} else{
		
		// 탈출조건을 만족하는지.
		if(indice_src_.size() >= MIN_DEPTH){
		
		}
		
		// Back!
		
		// visit 표시
	}
	
}
int main(){
	// in : (u, v) 좌표
	// out : ccw ordered permutation list
	
//	vector<Pos> positions;
//	positions.emplace_back(0, 10);
//	positions.emplace_back(0, 10);
//	positions.emplace_back(0, 10);
//	positions.emplace_back(0, 10);

//	map<int, Pos>
	
	int n = 4;
	vector<int> indice_;
	
	for(int i=0; i<n; i++){
		indice_.push_back(i);
	}
	
	// 초기 2개 뽑기
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i != j){
				
				vector<int> indice_src = {i, j};
				cout << "indice: " << indice_src << endl;
				
				queue<int> indice_remain;
				cout << "indice_remain: ";
				for(int k=0; k<n; k++){
					if(k!=i  && k!=j){
						indice_remain.push(k);
						cout << k << " ";
					}
				}
				cout << endl;
				
				perms();
				
			}
			
		}
	}
	
}
#endif



//#define BASIC_TEST
#ifdef BASIC_TEST
int main() {
	// in : 조합 요소 개수
	// out : combination
	vector<Combination> comb_tree;
	int n = 8;
	
	cout << "++ Comb tree Insertion Begin!! (" << n << ") ++" << endl;
	auto start_t = chrono::high_resolution_clock::now();
	
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
	
	auto end_t = chrono::high_resolution_clock::now();
	auto duration = end_t - start_t;
	
	cout << "++ Comb tree Insertion End!! (" << chrono::duration<double, std::micro>{duration}.count() << " us) ++" << endl << endl << endl;
	
	
	cout << "++ Comb tree Search Begin!! ++" << endl;
	vector<vector<int>> targets;
	targets.push_back({0, 2, 3});
	targets.push_back({1, 3, 0});
	targets.push_back({1, 1, 1});
	targets.push_back({1, 0, 3});
	targets.push_back({2, 1, 3, 0});
	targets.push_back({0, 1, 3, 2});
	targets.push_back({0, 4, 7, 6, 1, 2, 3, 5});
	
	vector<vector<Pos>> features;
	vector<double> micro_times;
	
	for(auto target : targets){
		
		start_t = chrono::high_resolution_clock::now();
		int base_ = target.front();
		vector<int> tmp;
		copy(target.begin(), target.end(), back_inserter(tmp));
		sort(tmp.begin()+1, tmp.end());
		
		cout << "Find " << target << " -> " << tmp << endl;
		
		vector<Pos> tmp_ret;
		if(comb_tree[base_].Search(tmp, tmp_ret)){
			micro_times.push_back(chrono::duration<double, std::micro>{chrono::high_resolution_clock::now()-start_t}.count());
			features.push_back(move(tmp_ret));
		} else{
			micro_times.push_back(0.f);
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
		cout << micro_times[i] << " us" << endl;
	}
	
	return 0;
}
#endif
