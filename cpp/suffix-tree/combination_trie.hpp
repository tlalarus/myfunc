#include <iostream>
#include <list>
#include <vector>
#include <deque>

#define MAX_SIZE 10

class CombinationTrieNode{
private:
    CombinationTrieNode* children[MAX_SIZE];
    float* features;
    int depth;
public:
    std::list<int> path;
    CombinationTrieNode(){
        path.clear();

        for(int i=0; i<MAX_SIZE; i++){
            children[i] = nullptr;
        }
        features = nullptr;
    }
    ~CombinationTrieNode(){
        if(features != nullptr){
            delete features;
        }
        for(int i=0; i<MAX_SIZE; i++){
            if(children[i] != nullptr){
                delete children[i];
            }
        }
    }

    void insertCombination_(std::deque<int>& comb, int index, int depth, std::list<int> path_);
    std::list<int> search(std::deque<int>& pat, float* features_);
    
};

using Node = CombinationTrieNode;

class CombinationTrie
{
private:
    Node root;
    int base;
    std::deque<int> indice;
public:
    CombinationTrie(std::deque<int> comb){
        int n = comb.size();
        indice = comb;
        base = indice[0];
        root.insertCombination_(indice, 0, 0, root.path);
    }

    void search(std::deque<int>& pat, float* features_);
    
};