#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>

/*
Question:
Given a dictionary based simple password, create all possible (special character) 
passwords based on a provided mapping.
Input: face
Map: {a -> @, 4, A}
Output: f@ce, f4ce, fAce
*/

std::unordered_map<char, std::vector<char>> lut = {{'a', {'@','4','A'}},
                                                   {'e', {'#', 'E'}},
                                                   {'b', {'0', '&'}}
                                                  };

void print_combinations(std::string str, std::unordered_set<std::string> &s, int i) {
  if (i == str.size()) {
    s.insert(str);
  }
  else {
    auto it = lut.find(str[i]);
    if (it != lut.end()) {
      for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
        str[i] = *it2;
        print_combinations(str, s, i+1);
      }
    }
    
    print_combinations(str, s, i+1);
  }
}

int main() {
  // your code goes here
  
  std::string str = "facebook";
  std::unordered_set<std::string> s;
  print_combinations(str, s, 0);
  
  for (auto &e : s) {
    std::cout << e << std::endl;
  }
  
  return 0;
}