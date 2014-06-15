#include <iostream>
#include <vector>
using namespace std;

/* Question:
Given a sorted array which is rotated n number of times. Find out how many times the array is rotated. 
Time complexity should be less than O(n).
*/

int binary_search(vector<int> &vec, int l, int r) {
  int min_element = vec[0];
  int min_element_index = 0;
  
  while (l <= r) {
    int mid = l + (r - l) / 2;
    
    if(vec[mid] < min_element) {
      min_element = vec[mid];
      min_element_index = mid;
    }
      
    if(vec[mid] <= vec[r]) {
      r = mid - 1;
    }
    else {
      l = mid + 1;
    }
  }
  
  return min_element_index;
}

int find_num_rot(vector<int> &vec) {
  if(vec.size() <= 1) {
    return -1;
  }

  int min_element_index = binary_search(vec, 0, vec.size() - 1);
  return vec.size() - min_element_index;
}

int main() {
  // your code goes here

  vector<int> vec = {3, 4, 5, 1, 2};
  cout << find_num_rot(vec);

  return 0;
}
