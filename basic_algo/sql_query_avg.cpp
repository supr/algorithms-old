#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
using namespace std;

int sql_query_avg_avg(const vector<int> &c1, const vector<string> &c2, const string &queryStr) {
  int sum = 0;
  int count = 0;
  
  for(int i = 0; i < c1.size(); i++) {
    if (c2[i] == queryStr) {
      // underflow detection
      if (sum < 0 && sum < (std::numeric_limits<int>::min() + c1[i])) {
        return -1;
      }
      
      // overflow detection
      // requirement: (num + new_integer) <= max_integer
      if (sum > 0 && sum > (std::numeric_limits<int>::max() - c1[i])) {
        return -1;
      }
      
      sum += c1[i];
      count++;
    } 
  }
  
  if (count == 0) {
    return -1;
  }
  
  return std::pow(sum / static_cast<float>(count), 2);
}

int main() {
  // your code goes here
  
  vector<int> c1 = {1,2,3,-4,-5,6,7,8,9,10};
  vector<string> c2 = {"monday", "tuesday", "wednesday", "thursday", "sunday", "sunday", "friday", "thursday", "sunday", "tuesday"};
  
  cout << sql_query_avg_avg(c1, c2, "sunday") << endl;
  
  return 0;
}