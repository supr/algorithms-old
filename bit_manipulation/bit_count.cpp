#include <iostream>
using namespace std;

// O(n) ... n is the number of binary digits
// Loop through all bits in an integer, check if 
// a bit is set and if it is then increment the set bit count
unsigned int bit_count1(unsigned int num) {
  unsigned int count = 0;
  
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
unsigned int bit_count2(unsigned int num) {
  unsigned int count = 0;
  
  while(num) {
    ++count;
    num = num & (num - 1); // If you subtract -1 from a given number it will convert the last "1" bit to "0"
  }                        // followed by continuous tail of 1, remove 1's tail by taking "&"
  
  return count;
}

// The best method for counting bits in a 32-bit integer v is the following:
// The best bit counting method takes only 12 operations, which is the same as the lookup-table method, 
// but avoids the memory and potential cache misses of a table. It is a hybrid between the purely parallel 
// method above and the earlier methods using multiplies (in the section on counting bits with 64-bit instructions), 
// though it doesn't use 64-bit instructions. The counts of bits set in the bytes is done in parallel, and the sum 
// total of the bits set in the bytes is computed by multiplying by 0x1010101 and shifting right 24 bits.
// reference: http://graphics.stanford.edu/~seander/bithacks.html
unsigned int bit_count3(unsigned int num) {
  unsigned int count = 0;
  
  num = num - ((num >> 1) & 0x55555555);                    // reuse input as temporary
  num = (num & 0x33333333) + ((num >> 2) & 0x33333333);     // temp
  count = ((num + (num >> 4) & 0xF0F0F0F) * 0x1010101) >> 24; // count
  
  return count;
}

unsigned int count_bits_float(float num) {
  union u {
      float num;
      int i;
  } u1;
  u1.num = num; // floating number to check
 
  unsigned int num_bits = 0;

  while (u1.i) {
      num_bits++;
      u1.i = u1.i & (u1.i-1);
  }
 
	return num_bits;
}

int main() 
{
  cout << bit_count1(15) << endl;
  cout << bit_count2(15) << endl;
  
  return 0;
}
