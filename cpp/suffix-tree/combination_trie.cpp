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

int main()
{
    deque<int> indice {3, 0, 1, 2, 4};
    cout << "INPUT {3, 0, 1, 2. 4}" << endl;

    

    vector<CombinationTrie> tries;
    cout << "vector push1" << endl;
    tries.emplace_back(indice);

    cout << endl << endl;
    deque<int> first{3, 0, 2, 4};

    vector<vector<float>> result;
    cout << "FIND {3, 0, 2, 4}" << endl;
    tries[0].search(first, result);

    cout << "Print result feature "<< result.size() << endl;
    for(auto&& fele : result){
        for(auto&& ele : fele){
            cout << ele << " ";
        }
        cout << endl;
    }

    deque<int> second{3,0,2,5};
    cout << " INPUT {3,0,2,5}" << endl;
    tries.emplace_back(second);
    cout << "program close" << endl;

    
}