/* 
Question:
Given an input string and a dictionary of words, find out if the input string can be segmented into a 
space-separated sequence of dictionary words. See following examples for more details.
This is a famous Google interview question, also being asked by many other companies now a days.

Consider the following dictionary 
{ this, is, a, test, of, my, algorithm}

input: thisisatestofmyalgorithm
output: this is a test of my algorithm
*/

#include <iostream>
using namespace std;

const int ALPHABET_SIZE = 26;

class Node {
public:
  bool isWord;
  bool isEnd;
  Node *next[ALPHABET_SIZE];
  Node(): isEnd(false) {}
};

class Trie {
private:
  Node *root;
  Node *curr;
  
  Node *allocateNodes() {
    Node *n = new Node;
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      n->next[i] = NULL;
    }
    
    return n;
  }
  
public:
  Trie() {
    root = allocateNodes();
  }
  
  void put(const string &s) {
    Node *curr = root;
    
    for (int i = 0; i < s.size(); i++) {
      char index = s[i] - 'a';
      
      if (!curr->next[index]) {
        curr->next[index] = allocateNodes();
      }
      
      curr = curr->next[index];
      curr->isEnd = false;
    }
    
    curr->isWord = true;
    curr->isEnd = true;
  }
  
  bool get(const char &c) {
    char index = c - 'a';
      
    if (!curr->next[index]) {
      return false;
    }
      
    curr = curr->next[index];
    
    if (curr->isWord) {
      curr->isWord = false;
      return true;
    }
    
    return false;
  }
  
  void reset() {
    curr = root;
  }
};

void splitWords(Trie &t, const string &str) {
  string currWord;
 
  t.reset();
  
  for (int i = 0; i < str.size(); i++) {
    currWord += str[i];
    
    if (t.get(str[i])) {
      cout << currWord << ' ';
      t.reset();  
      currWord.clear();
    }
  }
}

int main() {
  // your code goes here
  
  Trie t;
  t.put("this");
  t.put("is");
  t.put("a");
  t.put("test");
  t.put("of");
  t.put("my");
  t.put("algorithm");
  
  splitWords(t, "thisisatestofmyalgorithm");
  
  return 0;
}