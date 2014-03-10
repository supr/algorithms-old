#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Question:
Write an aligned malloc & free function that takes number of bytes and aligned byte 
(which is always power of 2)

Example:
align_malloc (1000,32) will return a memory address that is a multiple of 32 and 
that points to memory of size 1000 bytes 
aligned_free() will free memory allocated by align_malloc.
*/

void *aligned_malloc(size_t required_bytes, size_t alignment) {
    void *p1;
    void **p2;
    int offset = alignment - 1 + sizeof(void*); // max offset to an alignment byte is alignment + 1, e.g.
                                                // p1 = 31 dec, offset is 31 in order to align to address 0 (alignment is 32)
    p1 = malloc(required_bytes + offset);
    p2=(void**)(((size_t)(p1) + offset) & ~(alignment - 1));
    p2[-1] = p1;
    return p2;
}

void aligned_free( void* p ) {
    void* p1 = ((void**)p)[-1];         // get the pointer to the buffer we allocated
    free( p1 );
}

/*
- The strategy is to malloc more space than what we need (into p1), and return a p2 pointer somewhere after the 
beginning of the buffer.
- Since alignment is a power of two, in binary it has to form of 1 followed by zeros. e.g. if alignment is 32, it 
will be 00100000 in binary 
- (alignment-1) in binary format will turn the 1 into 0, and all the 0's after the 1 into 1. For example: (32-1) 
is 00011111
- the ~ will reverse all the bits. That is: 11100000
- now, p1 is a pointer to the buffer (remember, the buffer is larger by offset than what we need). we add offset to 
p1: p1+offset.
- So now, (p1+offset) is greater that what we want to return. We'll nil all the insignificant bits by doing a bitwise 
and: (p1+offset) & ~(offset-1)
- This is p2, the pointer that we want to return. Note that because its last 5 digits are zero it is 32 aligned, as 
requested.
- p2 is what we'll return. However, we must be able to reach p1 when the user calls aligned_free. For this, note that 
we reserved location for one extra pointer when we calculated the offset (that's the sizeof(void*) in line 4.
- so, we want to put p1 immediately before p2. This is p2[-1]. This is a little bit tricky calculation. Remember that 
p2 is defined as void*. One way to look at it is as array of void. C array calculation say that p2[0] is exactly p2. 
p2[1] is p2 + sizeof(void*). In general p2[n] = p2 + n*sizeof(void*). The compiler also supports negative numbers, 
so p2[-1] is one void* (typically 4 bytes) before p2.
*/
