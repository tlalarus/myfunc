#include "combination_trie.hpp"

using namespace std;

static int cnt = 0;
/**
 * @brief recursive 함수.
 * @param comb 마커번호 조합
 * @param index comb의 가장 처음 번호의 순서
 */
void Node::insertCombination_(std::deque<int>& comb, int index, int depth, std::list<int> path_)
{
    // {2 0 1 3 4}
    int n = comb.size(); // n=5
    int nc = n - index - 1;

    std::list<int>::iterator it;
    for(it=path_.begin(); it!=path_.end(); it++){
        path.push_back(*it);
    }
    
    path.push_back(comb[index]);

    cout << "\nInput children size="<< nc << ", this index=" << index <<" pathsize=" << path.size() << endl;
    
    if(n-index > 1){
        for(int i=index+1; i<n; i++){ //{0 1 3 4}, i=1,2,3,4

            if(children.find(comb[i])==children.end()){
                cout << "Create " << comb[index] << "'s children[" << comb[i] <<"]" << endl;
                children.insert({comb[i], Node()});
                
                cout <<"Insert {";
                for(int j=i; j<n; j++){
                    cout << comb[j] <<" ";
                }
                cout << "} to children[" << comb[i] << "]" << endl;
                
                children[comb[i]].insertCombination_(comb, i, depth+1, path);
            }
        }
    }
    else{
        // leaf node
        cout <<"    Leaf node " << comb[index] <<", depth="<< depth;
        // path 출력
        cout <<" path= {";
        for(auto&& ele : path){
            cout << ele << " ";
        }
        cout <<"}" << endl;

        features.resize(2);
        features[0].push_back(cnt++);
        features[1].push_back(cnt++);
        
        cout << "    features={" << features[0].front() <<" " <<features[1].front() << "}" << endl;
    }
}

std::list<int> Node::search(std::deque<int>& pat, std::vector<std::vector<float>>& features_)
{
    // if all index of pattern have been processed,
    cout << "Search {";
    for(auto&& ele : pat){
        cout << ele << " ";
    }
    cout <<"} " << endl;

    if(pat.size() == 0){
        cout << "pattern size is zero" << endl;
        if(!features.empty())
        for(int i=0; i<2; i++){
            features_.push_back(features[i]);
        }
        return path;
    }

    cout <<"this node's pathsize= " << path.size() << endl;
    if(children.find(pat[0]) != children.end()){
        deque<int> sub{pat.begin()+1, pat.begin()+pat.size()};
        cout << "Enter to children[" << pat[0] << "]" << endl;
        return (children[pat[0]].search(sub, features_));
    }

    list<int> none(0);
    return none;
}

void CombinationTrie::search(std::deque<int>& pat, std::vector<std::vector<float>>& features_)
{
    if(pat[0] != base){
        cout << "base is different" << endl;
    }
    deque<int> side{pat.begin()+1, pat.begin()+pat.size()};
    list<int> result_path = root.search(side, features_);

    if(result_path.empty()){
        cout << "pattern not found" << endl;
    }
    else{
        cout << "Print path= ";
        list<int>::iterator it;
        for(it = result_path.begin(); it!=result_path.end(); it++){
            cout << *it << " ";
        }
        cout << endl;
    }
}

void Node::display(int depth)
{
    if(depth == 0){
        // root node
        cout << path.back();
    }
    else{
        for(int i=0; i<depth-1; i++){
            cout << "....";
        }
        cout << "+-- " << path.back();
    }
    
    map<int, Node>::iterator it;
    if(it != children.end()){
        cout << endl;
    }
    for(it=children.begin(); it!=children.end(); it++){
        it->second.display(depth+1);        
    }

    if(children.size() == 0 || children.empty()){
        // Leaf node
        //cout << "Leaf node" << endl;
        //cout << endl;
    }
    
}

void CombinationTrie::display()
{
    //vector
    root.display(0);
}

// 노드의 현재 depth를 저장할 변수를 초기화한다. root node는 depth가 0이다.
// 현재 탐색하는 depth를 저장할 boolean array를 선언하고 false로 초기화한다.
// 만약 현재 노드가 루트이고 이 node가 depth가 0이면 노드의 데이터를 프린트한다.
// 아니면, 1부터 노드의 현재 뎁스까지 루프를 반복하고, "|   "를 탐색하는 뎁스에 대해서 프린트한다. 
// 비탐색하는 뎁스에 대해서는 "   "만 프린트한다.
// 현재 노드의 값을 프린트하고 개행한다.
// 현재 노드가 뎁스의 리프 노드이면 non-exploring으로 마크한다.
// 


int main()
{
    int n = 5;

    vector<CombinationTrie> tries;
    for(int i=0; i<n; i++){
        deque<int> indice;
        indice.push_back(i);

        for(int j=0; j<n; j++){
            if(i != j){
                indice.push_back(j);
                
            }
        }

        cout <<"@ Generate combination tree: " << endl;
        for(auto&& ele : indice){
            cout << ele << " ";
        }
        cout << endl;

        tries.emplace_back(indice);
    }

    cout <<" Num of Combination trie: " << tries.size() << endl;

    for(int i=0; i<n; i++){
        cout << "\n@@ Print node " << i << endl;
        tries[i].display();
    }

}