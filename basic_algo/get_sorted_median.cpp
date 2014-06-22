#include <iostream>
#include <vector>
#include <deque>
using namespace std;

/* Question:
Get the Median of two sorted arrays.
*/

float get_median_of_two_sorted_vec(const vector<int> &vec1, const vector<int> &vec2) {
  deque<int> median;
  bool median_two_elements = false;
  int len = vec1.size() + vec2.size();
  int i = 0;
  int j = 0;
  int median_index = len / 2;
  int index = 0;
  
  // the number of all elements is even -> 2 median elements
  if((len % 2) == 0) {
    median_two_elements = true;
  }
  
  while(index <= median_index) {
    if(!median.empty()) {
      median.pop_front();
    }
    
    if(vec1[i] < vec2[j]) {
      median.push_back(vec1[i]);
      i++;
    }
    else if(vec1[i] > vec2[j]) {
      median.push_back(vec2[j]);
      j++;
    }
    else {
      if(median_two_elements) {
        if(!median.empty()) {
          median.pop_front();
        }
        median.push_back(vec1[i]);  
      }
      
      median.push_back(vec1[i]);
      i++;
      j++;
      index++;
    }
    
    index++;
  }
      
  if(!median_two_elements) {
    return median[0];
  }
  
  return (median[0] + median[1]) / 2.0;
}

int main() {
  // your code goes here

  vector<int> vec1 = {1, 2, 5, 9, 15};
  vector<int> vec2 = {2, 3, 8, 10, 17, 22};
    
  cout << get_median_of_two_sorted_vec(vec1, vec2) << endl;
 
  vector<int> vec3 = {1, 1, 3, 4};
  vector<int> vec4 = {1, 2, 8, 9, 10};
    
  cout << get_median_of_two_sorted_vec(vec3, vec4) << endl; 

  vector<int> vec5 = {1, 1, 3, 4};
  vector<int> vec6 = {1, 2, 8, 9};
    
  cout << get_median_of_two_sorted_vec(vec5, vec6) << endl; 
  
  return 0;
}