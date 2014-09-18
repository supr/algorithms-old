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
#include <vector>
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
  int wordsCount;
  
public:
  trie() {
    wordsCount = 0;
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
      
      tmp->isEnd = false;
      tmp->count++;
    tmp = tmp->next[k];
    }
    
    tmp->isEnd = true;
    wordsCount++;
  }
  
  string findLongestCommonPrefix() {
    Node *tmp = root;
    string prefix;
    
    while(true) {
      bool found = false;
      int storeIndex = 0;
      
      for (int i = 0; i < alphabet_size; i++) {
        if (tmp->next[i] && 
            tmp->next[i]->count == wordsCount) {
          storeIndex = i;
          found = true;
        }
      }
      
      if (found) {
        prefix += static_cast<char>(storeIndex + 'a');
        tmp = tmp->next[storeIndex];
      }
      else {
        break;
      }
    }
    
    return prefix;
  }
};

int main() {
  // your code goes here
  
  trie t;
  
  vector<string> text = { 
    {"flower"}, 
    {"flow"}, 
    {"flight"}
  };
   
  for (int i = 0; i < text.size(); i++) {  
    t.insert(text[i]);
  }

  cout << t.findLongestCommonPrefix() << endl;
  
  return 0;
}