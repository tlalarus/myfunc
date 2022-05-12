#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <map>

class CombinationTrieNode{
private:
    std::map<int, CombinationTrieNode> children;
    std::vector<std::vector<float>> features;
    int depth;
public:
    std::list<int> path;
    CombinationTrieNode() {};
    ~CombinationTrieNode() {};

    void insertCombination_(std::deque<int>& comb, int index, int depth, std::list<int> path_);
    std::list<int> search(std::deque<int>& pat, std::vector<std::vector<float>>& features_);
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
    ~CombinationTrie() {};
    void search(std::deque<int>& pat, std::vector<std::vector<float>>& features_);
    
};