#include "suffix_trie.hpp"

using namespace std;

/**
 * @brief A rrecursive function to insert a suffix of the txt in subtree rooted with this node
 *
 */
void SuffixTrieNode::insertSuffix(string s, int index)
{
    // store index in linked list
    indexes->push_back(index);

    // if string has more characters
    if(s.length() > 0){
        // find the first character
        char cIndex = s.at(0);
        
        // if there is no edge for this character. add a new edge
        if(children[cIndex] == NULL){
            children[cIndex] = new SuffixTrieNode();
        }

        children[cIndex]->insertSuffix(s.substr(1), index+1);
    }
}

/**
 * @brief A recursive function to search a pattern in subtree rooted with this tree
 */
list<int>* SuffixTrieNode::search(string s)
{
    // if all charactoers of pattern have been processed,
    if(s.length() == 0){
        return indexes;
    }

    // if there is an edge from the current node of suffix trie,
    // follow the edge
    if(children[s.at(0)] != NULL){
        return (children[s.at(0)])->search(s.substr(1));
    }

    // if there is no edge, pattern doesn't exist in text
    else return NULL;
}

/**
 * @brief Prints all occurrences of pat in the suffix trie S(built for text)
 */
void SuffixTrie::search(string pat){
    // let us call recursive search function for root of trie.
    // we get a list of all indexes (where pat is present in text) in
    // variable 'result'

    list<int>* result = root.search(pat);

    //chect if the list of indexes is empty or not
    if(result == NULL){
        cout << "pattern not found"<< endl;
    }
    else{
        list<int>::iterator i;
        int patLen = pat.length();
        for(i=result->begin(); i!= result->end(); i++){
            cout << "Pattern found at position " << *i - patLen << endl;
        }
    }
}


int main(){
    // Let us build asuffix trie
    string txt = "geeksforgeeks.org";
    SuffixTrie S(txt);

    cout << "Search for 'ee'" <<endl;
    S.search("ee");

    cout << "\nSearch for 'geek'" << endl;
    S.search("geek");

    cout << "\nSearch for 'quiz'" << endl;
    S.search("quiz");

    cout << "\nSearch for 'forgeeks'" << endl;
    S.search("forgeeks");

    return 0;

    
}

