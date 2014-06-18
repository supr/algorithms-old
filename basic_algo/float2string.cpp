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
  
template <class T> 
string to_string(T t) 
{ 
    stringstream ss; 
    ss << t; 
    return ss.str(); 
} 
  
string float_to_string(float val, int n) 
{ 
    int integral = static_cast<int>(val); 
    float fractional = val - integral; 
    fractional = fractional * pow(10,n);
    
    string str = to_string<int>(integral) + 
                 '.' + 
                 to_string<int>(static_cast<int>(fractional)); 
  
    return str; 
} 
  
int main() 
{ 
    cout << float_to_string(7.64, 8) << endl; 
    return 0;
}