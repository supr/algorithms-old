#include <iostream>
using namespace std;

/* Question:
Implement a spin lock
*/

// Version 1: test_and_set
int value = 0; // Free
Acquire() {
  while (test&set(value)); // while busy
}

Release() {
  value = 0;
}
	
// Problem:	
// - test_and_set always goes to memory (bypasses caches) does not exploit caches
//   If your getAndSet is actually writing to the memory location, then you'll 
//   get dirtying of the cache line. You can use testing instead of plain setting for that.
//   If you mean multiple CPUs with many caches, then you may get worse effects.
// - introduces sequential overhead


// Version 2: test_and_test_and_set
// spin on read
int value = 0; // Free
Acquire() {
  while (true) {
    while(value); // Locked, spin with reads
    if (!test_and_set(value))
      break; // Success!
  }
}

Release() {
  value = 0;
}
			
// why is this better?
// exploits caching, goes to bus only when lock “looks” free

// Problem: 
// – Multiple processors spinning on same memory location
//   » Release/Reacquire causes lots of cache invalidation traffic
//   » No guarantees of fairness – potential livelock
// – Scales poorly with number of processors
//   » Because of bus traffic, average time until some processor 
//     acquires lock grows with number of processors
// - increased network traffic on lock release
// - busy waiting --> use exponential backoff

// Improvement:
// - use exponential backoff

// Use of Spinlock
// - only if the critical section is short
// - only on multicore systems
