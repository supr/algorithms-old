/* Question:
Long Subtraction -- Given two arrays A, B, each contains elements of digits, return an array of A - B. Your machine can only do 
calculation of less than 20. 
eg. A = [1,2,5,7,5]; 
B =       [3,4,8,9]; 
A - B =   [9,0,8,6];
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> calcDiff(vector<int> &in1, vector<int> &in2) {
  vector<int> diff;
  
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
  
  int carry_old = 0;
  int carry = 0;
  int digit = 0;
  
  for(int i = 0; i < in1.size(); i++) {
    carry = carry_old;
    
    if(in1[i] < in2[i]) {
      in1[i] += 10;
      carry_old = 1;
    } else {
      carry_old = 0;
    }
    
    digit = in1[i] - (in2[i] + carry);
    diff.push_back(digit);
  }
  
  if (digit == 0) {
    diff.pop_back();  
  }
  
  std::reverse(diff.begin(), diff.end());
  
  return diff;
}

int main() {
  // your code goes here
  
  vector<int> in1 = {1, 2, 5, 7, 5};
  vector<int> in2 = {3, 4, 8, 9};
  
  vector<int> sum = calcDiff(in1, in2);
  
  for(auto e : sum) {
    cout << e << ' '; 
  }
  
  return 0;
}