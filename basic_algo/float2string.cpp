#include <iostream>
#include <cmath>
#include <string>
using namespace std;

/*Question:
Given a float number 7.64, convert it into the string WITHOUT using any inbuilt function/library.
for eg:
input
float no.: 7.64
output
string: 7.64
*/

string int_to_string(int val) {
  int len = log10(val) + 1;
  string str;
  str.resize(len);
  int index = len - 1;
  
  while(index >= 0) {
    str[index] = '0' + (val % 10);
    val = val / 10;
    index--;
  }
  
  return str;
}

string float_to_string(float val) {
  int integ = static_cast<int>(val);
  int fract = 0;

  val = val - integ;
  while(val > 0) {
    val = val * 10;
    fract = (fract * 10) +  static_cast<int>(val);    
    val = val - static_cast<int>(val);
  }
  
  string str = int_to_string(integ) + '.' + int_to_string(fract);

  return str;
}

int main() {
  // your code goes here
  
  cout << float_to_string(7.64) << endl;
  
  return 0;
}