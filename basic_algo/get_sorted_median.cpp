#include <iostream>
#include <vector>
using namespace std;

void update_median_elements(int &median_element_left, int &median_element_right, int median_index_left, int index, int curr_element) {
  if(index < median_index_left) {
    median_element_left = curr_element;
  }
  else {
    median_element_right = curr_element;
  }
}

float get_median_of_two_sorted_vec(const vector<int> &vec1, const vector<int> &vec2) {
  int i = 0;
  int j = 0;
  int total_len = vec1.size() + vec2.size();
  int median_index_left = (total_len / 2) + (total_len % 2);
  int median_index_right = median_index_left;
  int index = 0;
  int median_element_left = 0;
  int median_element_right = 0;
  
  if((total_len % 2) == 0) {
    median_index_right++;
  }
  
  while(index < median_index_right) {
    if(i < vec1.size() && j < vec2.size()) {
      if(vec1[i] < vec2[j]) {
        update_median_elements(median_element_left, median_element_right, median_index_left, index, vec1[i]);
        i++;
      }
      else if(vec2[j] < vec1[i]) {
        update_median_elements(median_element_left, median_element_right, median_index_left, index, vec2[j]);
        j++;
      }
      else {
        update_median_elements(median_element_left, median_element_right, median_index_left, index, vec1[i]);
        index++;
        i++;
        j++;      
      }
    }
    else if(i < vec1.size()) {
      update_median_elements(median_element_left, median_element_right, median_index_left, index, vec1[i]);
      i++;
    }
    else if(j < vec2.size()) {
      update_median_elements(median_element_left, median_element_right, median_index_left, index, vec2[j]);
      j++;
    }

    index++;
  }
  
  if(median_index_left == median_index_right) {
    return median_element_left;
  }
  
  return (median_element_left + median_element_right) / 2.0;
}

int main() {
  // your code goes here

  vector<int> vec1 = {1, 2, 5, 9, 15};
  vector<int> vec2 = {2, 3, 8, 10, 17, 22};
    
  cout << get_median_of_two_sorted_vec(vec1, vec2) << endl;
  
  return 0;
}