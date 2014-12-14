/*
Question:
there are three shorted int Array 
A1: {2,4,9,16,19,68,78}
A2: {4,8,67,106,109,115,120}
A3: {9,15,19,108,119,130,190}

write an efficient algo to get the top 5 largest number from these three arrays. 

Function would be like 

sorted arrays:
vector<int> top5LargestNumber(const vector<int> &A1, const vector<int> &A2, const vector<int> &A3)

unsorted arrays:
vector<int> top5LargestNumber_unsorted(const vector<int> &A1, const vector<int> &A2, const vector<int> &A3)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

struct comparison {
  bool operator()(int a, int b) {
    return a > b;
  } 
};

void insert(priority_queue<int, vector<int>, comparison> &pq, int value) {
  if (pq.size() < 5) {
    pq.push(value);
  } else {
    if (value > pq.top()) {
      pq.pop();
      pq.push(value);
    }
  }
}

vector<int> top5LargestNumber_unsorted(const vector<int> &A1, const vector<int> &A2, const vector<int> &A3) {
  priority_queue<int, vector<int>, comparison> pq;
  vector<int> topElements;
  
  for (int i = 0; i < A1.size(); i++) {
    insert(pq, A1[i]);
  }
  
  for (int i = 0; i < A2.size(); i++) {
    insert(pq, A2[i]);
  }
  
  for (int i = 0; i < A3.size(); i++) {
    insert(pq, A3[i]);
  }
  
  while(!pq.empty()) {
    topElements.push_back(pq.top());
    pq.pop();
  }
  
  return topElements;
}

int main() {
  // your code goes here

  vector<int> A1 = {2,4,9,16,19,68,78};
  vector<int> A2 = {4,8,67,106,109,115,120};
  vector<int> A3 = {9,15,19,108,119,130,190};

  vector<int> top = top5LargestNumber(A1, A2, A3);

  for(auto const&  e : top) {
    cout << e << ' ';
  }

  cout << '\n';

  vector<int> A4 = {4,2,9,78,19,68,16};
  vector<int> A5 = {120,8,109,106,67,115,4};
  vector<int> A6 = {130,9,190,108,119,15,19};

  vector<int> top2 = top5LargestNumber_unsorted(A4, A5, A6);

  for(auto const&  e : top2) {
    cout << e << ' ';
  }

  return 0;
}