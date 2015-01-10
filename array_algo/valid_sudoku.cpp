/*
Question:
You're given a solution to a Sudoku puzzle. Write the code to check if it's a valid solution.
*/

#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

bool isValidSudoku(vector<vector<int>> &arr) {
  int rows = arr.size();
  int cols = arr[0].size();
  int smallGridSize = 3;
  
  // check cols for duplicates
  for (int row = 0; row < rows; row++) {
    unordered_set<int> hs;
      
    for (int col = 0; col < cols; col++) {
      auto it = hs.find(arr[row][col]);
      if (it == hs.end()) {
        hs.insert(arr[row][col]);
      }
      else {
        return false;
      }
    }
  }
  
  // check rows for duplicates
  for (int col = 0; col < cols; col++) {
    unordered_set<int> hs;
      
    for (int row = 0; row < rows; row++) {
      auto it = hs.find(arr[row][col]);
      if (it == hs.end()) {
        hs.insert(arr[row][col]);
      }
      else {
        return false;
      }
    }
  }
  
  // check duplicates within sub grid's
  for (int r = 0; r < cols; r+=smallGridSize) {
    for (int c = 0; c < cols; c+=smallGridSize) {
      int start_r = r;
      int start_c = c;
      unordered_set<int> hs;
        
      for (int row = 0; row < smallGridSize; row++) {
        for (int col = 0; col < smallGridSize; col++) {
          auto it = hs.find(arr[start_r+row][start_c+col]);
          if (it == hs.end()) {
            hs.insert(arr[start_r+row][start_c+col]);
          }
          else {
            return false;
          }
        }
      } 
    }
  }
  
  return true;
}

int main() {
  // your code goes here
  
  vector<vector<int>> arr = {{5, 3, 4, 6, 7, 8, 9, 1, 2},
                             {6, 7, 2, 1, 9, 5, 3, 4, 8},
                             {1, 9, 8, 3, 4, 2, 5, 6, 7},
                             {8, 5, 9, 7, 6, 1, 4, 2, 3},
                             {4, 2, 6, 8, 5, 3, 7, 9, 1},
                             {7, 1, 3, 9, 2, 4, 8, 5, 6},
                             {9, 6, 1, 5, 3, 7, 2, 8, 4},
                             {2, 8, 7, 4, 1, 9, 6, 3, 5},
                             {3, 4, 5, 2, 8, 6, 1, 7, 9}};
                 
  cout << isValidSudoku(arr) << endl;
  return 0;
}