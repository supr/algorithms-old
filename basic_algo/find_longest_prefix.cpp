/*
Question:
Longest Common Prefix from N strings of max length "m".
eg: 
Flower 
Flow 
Flight 

Output: 
Fl
*/

#include <iostream>
using namespace std;

const int alphabet_size = 26;

class Node {
public:
  Node *next[alphabet_size];
  bool isEnd;
  int count;
  
public:
  Node(): isEnd(false), count(0) {}
};

class trie {
private:
  Node *root;
  
public:
  trie() {
    root = createNode();
  }
  
  Node *createNode() {
    Node *n = new Node;
    
    for (int i = 0; i < alphabet_size; i++) {
      n->next[i] = NULL;
    }
    
    return n;
  }
  
  void insert(string str) {
    Node *tmp = root;
    
    for (int i = 0; i < str.size(); i++) {
      char k = str[i] - 'a';
      
      if (!tmp->next[k]) {
        tmp->next[k] = createNode();
      } 
    }
    
    tmp->isEnd = true;
    tmp->count++;
  }
};

int main() {
  // your code goes here
  
  trie t;
  
  return 0;
}