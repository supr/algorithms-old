#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Sort an array of characters into three groups, in O(n) time and using little extra memory.
*/

int find_middle(vector<int> &vec) {
    int min = *min_element(vec.begin(), vec.end());
    int max = *max_element(vec.begin(), vec.end());
    
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] > min && vec[i] < max) {
            return vec[i];
        }
    }
    
    return -1;
}

void three_way_parition(vector<int> &vec) {
    int middle = find_middle(vec);
    int i = 0;
    int j = 0;
    int n = vec.size() - 1;
    
    while (j <= n) {
        if (vec[j] < middle) {
            swap(vec[i], vec[j]);
            i++;
            j++;
        }
        else if (vec[j] > middle) {
            swap(vec[j], vec[n]);
            n--;
        }
        else {
            j++;
        }
    }
}

int main() {
  // your code goes here
  
  vector<int> vec = {1, 3, 2, 1, 3, 3, 2, 2, 1, 2};
  
  three_way_parition(vec);
  
  for (const auto &e : vec) {
    cout << e << ' ';
  }
  
  return 0;
}