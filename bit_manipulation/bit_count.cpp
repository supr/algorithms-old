#include <iostream>
using namespace std;

// O(n) ... n is the number of binary digits
// Loop through all bits in an integer, check if 
// a bit is set and if it is then increment the set bit count
int bit_count1(int num) {
  int count = 0;
  
  while(num != 0) {
    if ((num & 1)==1)
    count++;
    num = num >> 1;
  }

  return count;
}

// O(k) ... k is the number of '1's of binary number.
// Subtraction of 1 from a number toggles all the bits (from right to left) till the rightmost set 
// bit(including the righmost set bit). So if we subtract a number by 1 and do bitwise & with itself 
// (n & (n-1)), we unset the righmost set bit. If we do n & (n-1) in a loop and count the no of times loop 
// executes we get the set bit count.
int bit_count2(int num) {
  int count = 0;
  
  while(num) {
    ++count;
    num &= (num - 1);
  }
  
  return count;
}

int main() 
{
  cout << bit_count1(15) << endl;
  cout << bit_count2(15) << endl;
  
  return 0;
}
