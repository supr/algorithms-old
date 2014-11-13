/*
Question:
there are three shorted int Array 
A1: {2,4,9,16,19,68,78}
A2: {4,8,67,106,109,115,120}
A3: {9,15,19,108,119,130,190}

write an efficient algo to get the top 5 largest number from these three arrays. 

Function would be like 

vector<int> top5LargestNumber(const vector<int> &A1, const vector<int> &A2, const vector<int> &A3)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> top5LargestNumber(vector<int> A1, vector<int> A2, vector<int> A3) {
  int i = A1.size() - 1;
  int j = A2.size() - 1;
  int k = A3.size() - 1;
  vector<int> top;

  while(i > 0 || j > 0 || k > 0) {
    int max_element = 0;

    if (i >= 0) {
      max_element = A1[i];
      i--;
    } 
    if (j >= 0) {
      if (A2[j] > max_element) {
        max_element = A2[j];
        i++;
        j--;
      }
    } 
    if (k >= 0) {
      if (A3[k] > max_element) {
        max_element = A3[k];
        j++;
        k--;
      }
    }

    top.push_back(max_element);

    if (top.size() == 5) {
      break;
    }
  }

  return top;
}

int main() {
  // your code goes here

  vector<int> A1 = {2,4,9,16,19,68,78};
  vector<int> A2 = {4,8,67,106,109,115,120};
  vector<int> A3 = {9,15,19,108,119,130,190};

  vector<int> top = top5LargestNumber(A1, A2, A3);

  for(auto e : top) {
    cout << e << ' ';
  }

  return 0;
}