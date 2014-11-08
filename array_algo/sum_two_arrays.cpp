/* Question:
You have two integer arrays. 
Treat these arrays as if they were big numbers, with one digit in each slot. 
Perform addition on these two arrays and store the results in a new array.
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> calcSum(vector<int> &in1, vector<int> &in2) {
  vector<int> sum;
  
  std::reverse(in1.begin(), in1.end());
  std::reverse(in2.begin(), in2.end());
  
  // zero padding
  int lenDiff = abs(in1.size() - in2.size());
  if(in1.size() < in2.size()) {
    for(int i = 0; i < lenDiff; i++) {
      in1.push_back(0);
    }
  } else if(in2.size() < in1.size()) {
    in2.push_back(0);
  }
  
  int carry = 0;
  int digit = 0;
  
  for(int i = 0; i < in1.size(); i++) {
    digit = in1[i] + in2[i] + carry;
    carry = digit / 10;
    
    if (carry > 0) {
      digit = digit % 10;
    }
    
    sum.push_back(digit);
  }
  
  if(carry > 0) {
    sum.push_back(carry);
  }
  
  std::reverse(sum.begin(), sum.end());
  
  return sum;
}

int main() {
  // your code goes here
  
  vector<int> in1 = {1, 2, 3, 4, 5};
  vector<int> in2 = {9, 6, 7, 8, 9};
  
  vector<int> sum = calcSum(in1, in2);
  
  for(auto e : sum) {
    cout << e << ' '; 
  }
  
  return 0;
}