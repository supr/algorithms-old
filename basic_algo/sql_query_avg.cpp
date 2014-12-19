#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
using namespace std;

// under/overflow detection:
// - You can check if the addition is safe before you do it:
//   e.g. overflow: if (sum > 0 && sum > (numeric_limits<int>::max() - c1[i]))
//
// - an other option is checking the overflow flag with intrinsics -> they're compiler intrinsics
//   meaning they'll emit a certain assembly instruction, depending on your architecture
//   your compiler already knows when an overflow occurred
//   it's a bit in the status flag, called the carry flag
//   (i.e. there was a carry out of the last adder)
//   A new set of built-in functions for arithmetics with overflow checking has been added: 
//   __builtin_add_overflow, __builtin_sub_overflow and __builtin_mul_overflow and for compatibility 
//   with clang also other variants.
//
// - use inline asm is also possible:
//   "setc" means "set this memory location if the carry bit is 1"
//   setc eax means set eax to be 1 if carry bit was 1 in the status flag
//
//   #define add64(a,b,c)                            \
//   do                                              \
//   {                                             \
//      __asm__ __volatile__                        \
//        (                                         \
//        "add %2, %1 \n"                      \
//        "setc  %0     \n"                      \
//        : "=q" (c), "+q" (a)                     \
//        : "q" (b)                                \
//        );                                       \
//   }                                             \
//   while (0)

int sql_query_avg_avg(const vector<int> &c1, const vector<string> &c2, const string &queryStr) {
  int sum = 0;
  int count = 0;
  
  for(int i = 0; i < c1.size(); i++) {
    if (c2[i] == queryStr) {
      // underflow detection
      if (sum < 0 && sum < (numeric_limits<int>::min() + c1[i])) {
        return -1;
      }
      
      // overflow detection
      // requirement: (num + new_integer) <= max_integer
      if (sum > 0 && sum > (numeric_limits<int>::max() - c1[i])) {
        return -1;
      }
      
      sum += c1[i];
      count++;
    } 
  }
  
  if (count == 0) {
    return -1;
  }
  
  return std::pow(sum / static_cast<float>(count), 2);
}

int main() {
  // your code goes here
  
  vector<int> c1 = {1,2,3,-4,-5,6,7,8,9,10};
  vector<string> c2 = {"monday", "tuesday", "wednesday", "thursday", "sunday", "sunday", "friday", "thursday", "sunday", "tuesday"};
  
  cout << sql_query_avg_avg(c1, c2, "sunday") << endl;
  
  return 0;
}