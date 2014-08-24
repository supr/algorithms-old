#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
input the size of Matrix in N X M, input 0 , 1 , or 2 in all the location, and as 
2 can kill everyone that is in up and right and left direction, i have to find if 
there is any one who have not been killed.

e.g. input matrix:
01000111 
02012020 
02102100

final matrix:
0x00x1x1
xxxxxxxx
xxxxxxxx
*/

void printMatrix(const vector<vector<int>> &m) {
  for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < m[i].size(); j++) {
      cout << m[i][j] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

typedef struct rowMinMax {
  int min;
  int max;
  rowMinMax(int mi, int ma): min(mi), max(ma) {} 
}rowMinMax;

typedef struct index {
  int row;
  int col;
  index(int r, int c): row(r), col(c) {}
}index;

bool doesNoneKilledOneExist(const vector<vector<int>> &m) {
  unordered_set<int> killedCols;
  vector<index> foundOnes;
  
  for(int i = m.size() - 1; i >= 0; i--) {
    bool foundTwo = false;
    int vecSize = foundOnes.size();
    
    for(int j = 0; j < m[i].size(); j++) {
      if(m[i][j] == 2) {
        killedCols.insert(j);
        foundTwo = true;
      }
    
      auto it = killedCols.find(j);
      
      if(m[i][j] == 1 && it == killedCols.end()) {
        foundOnes.push_back(index(i, j));
      }
      
      if(it != killedCols.end()) {
        int index = 0;
        
        while(index < foundOnes.size()) {
            if (foundOnes[index].col == j) {
              vecSize--;
                foundOnes.erase(foundOnes.begin() + index);
            } else {
                ++index;
            }
        }
      }
    }
    
    if(!foundOnes.empty() && foundTwo) {
      foundOnes.erase(foundOnes.begin() + vecSize, foundOnes.end());
    }
  }
  
  for_each(foundOnes.begin(), foundOnes.end(), [](index ind) { cout << ind.row << ", " << ind.col << endl; });
  
  if (!foundOnes.empty()) {
    return true;
  }
  return false;
}

int main() {
  // your code goes here
  
  vector<vector<int>> m = {{0,1,0,0,0,1,1,1},
                           {0,2,0,1,2,0,2,0},
                           {0,2,1,0,2,1,0,0}};
                              
  printMatrix(m);
  
  cout << doesNoneKilledOneExist(m) << endl;

  vector<vector<int>> m2 = {{0,1,2,0,0,1,1,1},
                           {0,2,0,1,2,0,2,0},
                           {0,1,1,0,1,1,0,0}};
                              
  printMatrix(m2);
  
  cout << doesNoneKilledOneExist(m2) << endl;
  
  return 0;
}