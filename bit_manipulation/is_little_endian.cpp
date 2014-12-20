#include <iostream>
#include <cstdint>
using namespace std;

/* Question: 
Write a function that determines whether a computer is big-endian
or little-endian.
*/
  
/*
Little and big endian are two ways of storing multibyte data-types ( int, float, etc). 
In little endian machines, last byte of binary representation of the multibyte data-type 
is stored first. 
On the other hand, in big endian machines, first byte of binary representation of the 
multibyte data-type is stored first.

Suppose integer is stored as 4 bytes: 0x12345678
Memory Address: 0x10 0x11 0x12 0x13
Little Endian:  78   56   34   12
Big Endian:     12   34   56   78

*/

bool is_little_endian() { 
    union { 
        uint32_t idata; 
        char cdata[4]; 
    }endian_test; 
    
    endian_test.idata = 0x12345678; 
    
    if(endian_test.cdata[0] == 0x78) { 
        return true; 
    } 
    
    return false; 
} 

bool is_little_endian2() { 
   uint32_t i = 1;
   uint8_t *c = (uint8_t*)&i;
   if (*c) {    
       return true;
   }
   return false;
}

int main() {    
    // your code goes here
    cout << is_little_endian() << endl; 
    cout << is_little_endian2() << endl; 

    return 0; 
}