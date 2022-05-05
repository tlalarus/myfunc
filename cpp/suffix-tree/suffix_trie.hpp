/**
 * @brief A simple implement of substring search using trie of
 */

#include <iostream>
#include <list>
#define MAX_CHAR 256
using namespace std;

class SuffixTrieNode{

private:
    SuffixTrieNode * children[MAX_CHAR];
    list<int> *indexes;
public:
    SuffixTrieNode(){
        // Create an empty linked list for indexes of
        // suffixes startin from this node
        indexes = new list<int>;

        // Initialize all child pointer as NULL
        for(int i=0; i<MAX_CHAR; i++){
            children[i] = NULL;
        }
    }
    // A recursive function to insert a suffix of the txt
    // in subtree rooted with this node.
    void insertSuffix(string suffix, int index);

    // A function to search a pattern in subtree rooted
    // with this node. the function returns pointer to a linked
    // list containing all indexes where pattern is present.
    // The returned indexes are indexes of last characters
    // of matched text.
    list<int>* search(string pat);
    
};

// A trie of all suffixes
class SuffixTrie
{
private:
    SuffixTrieNode root;
public:
    // constructor (builds a trie of suffixes of  the given text)
    SuffixTrie(string txt){
        // consider all suffixes of given string and insert
        // them into the suffix trie using recursive function
        // insertsuffix in suffixtrienode class
        for(int i=0; i<txt.length(); i++){
            root.insertSuffix(txt.substr(i), i);
        }
    }

    // function to searches a patterns in this suffix trie.
    void search(string pat);
};