/* 
Question:
Print all possible words from phone digits

Given a keypad as shown in diagram, and a n digit number, list all words which are 
possible by pressing these numbers.
For example if input number is 234, possible words which can be formed are (Alphabetical order):
adg adh adi aeg aeh aei afg afh afi bdg bdh bdi beg beh bei bfg bfh bfi cdg cdh cdi ceg 
ceh cei cfg cfh cfi
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

template <class T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
  os << "{";
  for (const auto& elem : v)
  {
    os << " " << elem;
  }
  os << " }";
  return os;
}

std::vector<std::string> foo(std::vector<int> list, const std::unordered_map<int, std::vector<std::string>> ht) {
    if(list.size()==1) {
        std::vector<std::string> ret;
        for(const auto& e: ht.at(list.at(0))) {
            ret.push_back(e);
        }
        return ret;
    }
    int last = list.back();
    list.pop_back();
    
    std::vector<std::string> tail = foo(list, ht);
    // tail would be: G, H, I after the first recursion
        
    std::vector<std::string> ret;
    
    // we take the last number in the list: 3 and look for the mapping: D, E, F
    // the first return would add add those combinations:
    // DG, DH, DI, EG, EH, EI, FG, FH, FI
    for(const auto& e : ht.at(last)) {
        for(const auto& t: tail) {
            ret.push_back(e+t);
        }
    }
    return ret;
}

int main() {
    std::unordered_map<int, std::vector<std::string>> ht = {{2, {"A","B","C"}},
        {3, {"D","E","F"}},
        {4, {"G","H","I"}},
        {5, {"J","K","L"}},
        {6, {"M","N","O"}},
        {7, {"P","Q","R","S"}},
        {8, {"T","U","V"}},
        {9, {"W","X","Y","Z"}}};
    std::vector<int> list {4,3,2};

    std::cout << foo(list,ht) << std::endl;

    return 0;
}