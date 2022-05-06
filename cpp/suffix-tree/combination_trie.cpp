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
        
            if(children[comb[i]] == nullptr){
                cout << "Create " << comb[index] << "'s children[" << comb[i] <<"]" << endl;
                children[comb[i]] = new Node(); // children[0], children[1], children[3], children[4]
                
                cout <<"Insert {";
                for(int j=i; j<n; j++){
                    cout << comb[j] <<" ";
                }
                cout << "} to children[" << comb[i] << "]" << endl;
                
                children[comb[i]]->insertCombination_(comb, i, depth+1, path); // {1 3 4}
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
        features = new float[2];
        features[0] = cnt++;
        features[1] = cnt++;
        cout << "    features={" << features[0] <<" " <<features[1] << "}" << endl;
    }
}

std::list<int> Node::search(std::deque<int>& pat, float* features_)
{
    // if all index of pattern have been processed,
    cout << "Search {";
    for(auto&& ele : pat){
        cout << ele << " ";
    }
    cout <<"} " << endl;

    if(pat.size() == 0){
        cout << "pattern size is zero" << endl;
        for(int i=0; i<2; i++){
            features_[i] = features[i];
        }
        return path;
    }

    cout <<"this node's pathsize= " << path.size() << endl;
    if(children[pat[0]] != nullptr){
        deque<int> sub{pat.begin()+1, pat.begin()+pat.size()};
        cout << "Enter to children["<< pat[0] << "]" <<endl;
        return (children[pat[0]]->search(sub, features_));
    }    
    
    list<int> none(0);
    return none;
}


void CombinationTrie::search(std::deque<int>& pat, float* features_)
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

int main()
{
    deque<int> indice {3, 0, 1, 2, 4};
    cout << "INPUT {3, 0, 1, 2. 4}" << endl;

    CombinationTrie C(indice);

    cout << endl << endl;
    deque<int> first{3, 0, 2, 4};
    float result[2] = {-1, -1};
    cout << "FIND {3, 0, 2, 4}" << endl;
    C.search(first, result);

    cout << "Print result feature "<< endl;
    cout << result[0] << " " << result[1] << endl;

    deque<int> second{3,0,2,5};
    float result_second[2] = {-1, -1};
    cout << "FIND {3, 0, 2, 5}" << endl;
    C.search(second, result_second);
    cout << "Print result feature "<< endl;
    cout << result_second[0] << " " << result_second[1] << endl;

    
}