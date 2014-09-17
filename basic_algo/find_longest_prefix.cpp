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
private:
  Node *next;
  bool isEnd;
  int count;
  
public:
  Node(): next(NULL), isEnd(false), count(0) {}
};

class trie {
private:
  Node *root[alphabet_size];
  
public:
  trie() {
    for(int i = 0; i < alphabet_size; i++) {
      root[i] = new Node;
    }
  }
  
  void insert(string str) {
    for (int i = 0; i < alphabet_size; i++) {
      if (i == ('z' - str[i])) {
        root[i]->count++;
      } 
    }
    
  }
};

int main() {
  // your code goes here
  
  trie t;
  
  return 0;
}