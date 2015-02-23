#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/* Question:
Longest Consecutive Sequence

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
Your algorithm should run in O(n) complexity.
*/

vector<int> find_long_consec_sequ(vector<int> &vec) {
  unordered_set<int> hs;
  vector<int> indices;
  int max = 0;
  
  for (const auto &e : vec) {
    hs.insert(e);
  }
  
  for (const auto &e : vec) {
    int left = e - 1;
    int right = e + 1;
    int count = 1;
    vector<int> indices_tmp = {e};
    
    while (hs.find(left) != hs.end()) {
      indices_tmp.push_back(left);
      hs.erase(left);
      count++;
      left--;
    }
    
    while (hs.find(right) != hs.end()) {
      indices_tmp.push_back(right);
      hs.erase(right);
      count++;
      right++;
    }
    
    if (count > max) {
      max = count;
      indices = indices_tmp;
    }
  }
  
  return indices;
}

int main() {
  // your code goes here
  
  vector<int> vec = { 100, 4, 200, 1, 3, 2 };
  vector<int> seq = find_long_consec_sequ(vec);
  
  for (const auto &e : seq) {
    cout << e << ' ';
  }
  
  return 0;
}