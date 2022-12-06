#include <iostream>
#include <vector>
#include <queue>
#include <map>

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
};

class Node{
	vector<int> path;
	map<int, Node> children;
	bool leaf;
	int depth;
	
public:
		Node() {};
	void InsertNode(vector<int>& indice_in_, vector<int>& path_, int concat_idx, int depth_);
	void SearchNode(vector<int>& path_in_);
	
};

void Func(){
	cout << "Gen Feature" << endl << endl;
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
		Func();
	}

}


// 생성시 : combination(순서고려X)의 feature를 저장한다. ccw ordered permutation list를 생성한다.
// 검색시 : ccw ordered permutation list를 돌면서 feature를 rearrange 한다.
class Combination{
public:
	Node root;
	Combination() {};
	Combination(vector<int>& indice_);
	bool Search(vector<int>& path_in_);
};

Combination::Combination(vector<int>& indice_) {
	// sorted indice 입력받음
	vector<int> path_init;
	root.InsertNode(indice_, path_init, 0, 0);
}

void GetPermList(){

}

int main() {
	// in : (u,v) 좌표들
	// out : ccw 정렬된 (u,v) 좌표 조합들
	vector<Combination> comb_tree;
	int n = 4;
	for(int i=0; i<n; i++){
		vector<int> indice;
		indice.push_back(i);
		for(int j=0; j<n; j++){
			if(i != j){
				indice.push_back(j);
			}
		}
//		cout << " Input queue: ";
//		while(!indice.empty()){
//			cout << indice.front() << " ";
//			indice.pop();
//		}
//		cout << endl;
		
		comb_tree.emplace_back(indice);
	}
	
	
	return 0;
}
