#include <iostream>
#include <cstdint>
using namespace std;

/* Question: 
Write a function that determines whether a computer is big-endian
or little-endian.
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
  
int main() {    
    // your code goes here
    cout << is_little_endian() << endl; 
    
    return 0; 
}