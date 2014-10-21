#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/* Question:
Given two sequences, find the longest common subsequence present in both of them.

Algorithm:
- create a table of size m x n

  initialize the first row and first col to 0:

      A  B  A  C  E  B
     _________________
  A |_0|_0|_0|_0|_0|_0|
  D |_0|__|__|__|__|__|
  B |_0|__|__|__|__|__|
  A |_0|__|__|__|__|__|
  V |_0|__|__|__|__|__|
  C |_0|__|__|__|__|__|
  E |_0|__|__|__|__|__|
  B |_0|__|__|__|__|__|
     
- compare row letter with col letter
  - if there is no match: 
   
   -------
  |   | c |
  --------
  | b | r |
  ---------      r = max(b,c)

  - if there is a match:  

   -------
  | a |   |
  --------
  | a |a+1|
  ---------    ... creates a bridge

- backtrack

  select one of the 2 options to move (left + up, up + left):
  ^     <---
  |        ^ 
  |        |
  <---     |

  go to a different area only via a bridge

  the LCS are those letters which created the bridge


Complexity:
O(m * n)

algorithm explanation: https://www.youtube.com/watch?v=wJ-rP9hJXO0
*/

int lookup(const vector<vector<int>> &LCS, int i, int j) {
  if(i < 0 || j < 0) {
      return 0;
  }
  return LCS[i][j];
}

vector<int> longest_common_subseq(const vector<int> &X, const vector<int> &Y) {
  vector<vector<int>> LCS(Y.size() + 1, vector<int>(X.size() + 1, 0));
  int max_len = 0;
  int index_i = 0;
  int index_j = 0;

  for (int i = 1; i < X.size(); i++) {
    for (int j = 1; j < Y.size(); j++) {
      if (X[i-1] == Y[j-1]) {
        LCS[i][j] = 1 + LCS[i - 1][j - 1];
      }
      else {
        LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
      }
			
      if(LCS[i][j] > max_len) {
        max_len = LCS[i][j];
        index_i = i;
        index_j = j;
      }
    }
  }

  vector<int> result;
    
  while(index_i >= 0 && index_j >= 0) {
    if(X[index_i] == Y[index_j]) {
      result.push_back(X[index_i]);
      index_i--;
      index_j--;
    }
    else {
      if(lookup(LCS, index_i - 1, index_j) > 
        lookup(LCS, index_i, index_j - 1)) {
        index_i--;
      }
      else {
        index_j--;
      }
    }
  }
	
  /*
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cout << LCS[i][j] << ' ';
    }
    cout << '\n';
  }
  */
    
  std::reverse(result.begin(), result.end());
	
  return result;
}

int main() {
  // your code goes here

  vector<int> x = { 'A', 'B', 'A', 'C', 'E', 'B' };
  vector<int> y = { 'A', 'D', 'B', 'A', 'V', 'C', 'E', 'B' };

  vector<int> result = longest_common_subseq(x, y);
  for_each(result.begin(), result.end(), [](char val) { cout << val << ' '; });

  return 0;
}
