#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
using namespace std;

/* Question:
Question: How to get the median from a stream of numbers at any time?
The median is middle value of numbers. If the count of numbers is even, the
median is defined as the average value of the two numbers in middle

if the current element is less than maxheap.top, then insert it into maxheap.  
if the current element is greater than minheap.top, then insert it into minheap.  
If neither of those are true, insert it into whichever heap has smaller size.  
Then, if necessary, pop an element from the smaller size heap and insert it 
into the larger size heap, to keep their sizes within 1 of each other

Time Complexity: O(log(n))
Space Complexity: O(n)
*/

class MedianStream {
private:
  // stores all numbers smaller than the median
  priority_queue<int, vector<int>, std::greater<int>> min_heap;
  // stores all number greater than the median
  priority_queue<int, vector<int>, std::less<int>> max_heap;
  
public:
  void insert(int value) {
    if(min_heap.size() == 0 && max_heap.size() == 0) {
      min_heap.push(value);
    }
    // if the current element is greater than minheap.top, then insert it into minheap.  
    else if(value > min_heap.top()) {
      if(min_heap.size() > max_heap.size()) {
        int top = min_heap.top();
        min_heap.pop();
        max_heap.push(top);
      }
      min_heap.push(value);
    }
    // if the current element is less than maxheap.top, then insert it into maxheap. 
    else if(value < max_heap.top()) {
      if(max_heap.size() > min_heap.size()) {
        int top = max_heap.top();
        max_heap.pop();
        min_heap.push(top);
      }
      max_heap.push(value); 
    }
    // If neither of those are true, insert it into whichever heap has smaller size.  
    else {
      if(max_heap.size() < min_heap.size()) {
        max_heap.push(value);
      }
      else {
        min_heap.push(value);
      }
    }
  }
  
  float get_median() {
      if(min_heap.size() > max_heap.size()) {
        return min_heap.top();
      }
      else if(max_heap.size() > min_heap.size()) {
        return max_heap.top();
      }
      return (min_heap.top() + max_heap.top()) / 2.0;
  }
};

int main() {
  // your code goes here

  vector<int> vec1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  
  MedianStream m1; 
  for (int i = 0; i < vec1.size(); i++) {
  m1.insert(vec1[i]);
  cout << m1.get_median() << ' ';
  }
  cout << endl;

  vector<int> vec2 = { 1, 5, 3, 2, 8, 9 };
  
  MedianStream m2; 
  for (int i = 0; i < vec2.size(); i++) {
  m2.insert(vec2[i]);
  cout << m2.get_median() << ' ';
  }
  cout << endl;
  
  return 0;
}