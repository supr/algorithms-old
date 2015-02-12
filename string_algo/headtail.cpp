#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
using namespace std;

/*
Given two English words of the same length, say, "HEAD" and "TAIL", come up with a 
sequence of valid English words, starting with "HEAD", and ending with "TAIL", such 
that each word is formed by changing a single letter of the previous word.
*/

vector<string> generateCandidate(const string &current, const unordered_set<string> &dict) {
  const string alphabet = "abcdefghijklmnopqrestuvwxyz";
  vector<string> candidates;
  
  for (int i = 0; i < current.size(); i++) {
    string candidate = current;
    
    for (int j = 0; j < alphabet.size(); j++) {
      candidate[i] = alphabet[j]; 
      
      if (candidate == current) {
        continue;
      }
      
      auto it = dict.find(candidate);
      if (it != dict.end()) {
        candidates.push_back(candidate);
        break;
      }
    }
  }
  
  return candidates;
}

vector<string> getReachables(const string &current, const unordered_set<string> &dict) {
  vector<string> reachables;
  reachables = generateCandidate(current, dict);
  return reachables;
}

vector<string> bfsGoalNodes(const string &start, const string &goal, const unordered_set<string> &dict) {
  vector<string> sequence;
  queue<string> q;
  unordered_set<string> visited;
  q.push(start);
  
  while (!q.empty()) {
    string current = q.front();
    q.pop();
    
    auto it = visited.find(current);
    if (it != visited.end()) {
      continue;
    }
    visited.insert(current);
    
    sequence.push_back(current);
    
    if (current == goal) {
      return sequence;
    }
    
    vector<string> reachables = getReachables(current, dict);
    
    for (auto &reachable : reachables) {
      q.push(reachable);
    }
  }
}

int main() {
  // your code goes here
  
  unordered_set<string> dict_4_letters = {"head", "heal", "teal", "tell", 
                                          "tall", "tail", "mike", "rolf"};
 
  vector<string> sequence = bfsGoalNodes("head", "tail", dict_4_letters);
  
  for (auto &e : sequence) {
    cout << e << endl;  
  }
  
  return 0;
}