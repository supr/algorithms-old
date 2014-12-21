#include <iostream>
#include <queue>
using namespace std;

/* Question:
return the k smallest elements from a heap of size n
*/

typedef priority_queue<int, vector<int>, std::less<int>> p_queue; // max heap

p_queue get_k_smallest_elements(queue<int> &q, int k) {
  p_queue max_heap;
  
  while (!q.empty()) {
    int e = q.front();
    q.pop();
    
    if (max_heap.size() < k) {
      max_heap.push(e);
    } else {
      int top = max_heap.top();
      if (e < top) {
        max_heap.pop();
        max_heap.push(e);
      }
    }
  }
  
  return max_heap;
}

int main() {
  // your code goes here
  
  queue<int> q;
  q.push(1);
  q.push(5);
  q.push(19);
  q.push(3);
  q.push(5);
  q.push(22);
  q.push(23);
  q.push(18);
  q.push(2);
  q.push(4);
  q.push(99);
  q.push(1);
  
  p_queue max_heap = get_k_smallest_elements(q, 4);
  
  while (!max_heap.empty()) {
    cout << max_heap.top() << ' ';
    max_heap.pop();
  }
  
  return 0;
}