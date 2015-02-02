/*
Question:
Given a list of strings, return a list of lists of strings that groups all anagrams. 

Ex. given {trees, bike, cars, steer, arcs} 
return { {cars, arcs}, {bike}, {trees, steer} } 

m = # of words 
n = length of longest word 

I solved this in O(m * n * log n) time.
*/

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef map<string, vector<string>> myMap;

myMap group_anagrams(vector<string> &vec) {
  myMap m;
  
  for (auto it = vec.begin(); it != vec.end(); it++) {
    string copy(*it);
    
    sort(it->begin(), it->end());
    
    auto it2 = m.find(*it);
    
    if (it2 == m.end()) {
      vector<string> e;
      e.push_back(copy);
      m[*it] = e;
    } else {
      it2->second.push_back(copy);
    }
  }
  
  return m;
}

int main() {
  vector<string> vec = {"trees", "bike", "cars", "steer", "arcs"};
  
  myMap m = group_anagrams(vec);
  
  for (auto it : m) {
    cout << "group \"" << it.first << "\": " << endl;

    for (auto it2 = it.second.begin(); it2 != it.second.end(); it2++) {
      cout << *it2 << '\n';
    }

    cout << "\n";
  }

  return 0;
}