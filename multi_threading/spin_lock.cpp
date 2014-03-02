#include <iostream>
using namespace std;

/* Question:
Implement a spin lock
*/

// Version 1:
lock:
	while (test_and_set(lock) == locked);
unlock:
	lock = unlocked;
	
// Problem:	
// - test_and_set always goes to memory (bypasses caches) does not exploit caches
//   If your getAndSet is actually writing to the memory location, then you'll 
//   get dirtying of the cache line. You can use testing instead of plain setting for that.
//   If you mean multiple CPUs with many caches, then you may get worse effects.
// - introduces sequential overhead

// Version 2:

// spin on read (test_and_set)
lock:	while (lock == busy) spin;
	if (test_and_set(lock) == busy) goto lock;
			
// why is this better?
// exploits caching, goes to bus only when lock “looks” free

// Problem: 
// increased network traffic on lock release

// Use of Spinlock
// - only if the critical section is short
// - only on multicore systems
