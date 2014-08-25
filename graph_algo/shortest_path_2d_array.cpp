#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

/*
Given a matrix of MxN elements. Find the shortest path between a given source cell 
to a destination cell.
*/

class pos {
public:
  int row;
  int col;
  pos(int r, int c): row(r), col(c) {}
  bool operator==(const pos &rhs) { 
    return row == rhs.row && col == rhs.col;
  }
};

bool move(pos &curr, int maxCols, int maxRows) {
  if(curr.col - 1 >= 0) {
    curr.col =- 1;
    return true;
  } else if(curr.col + 1 < maxCols) {
    curr.col =+ 1;
    return true;
  } else if(curr.row - 1 >= 0) {
    curr.row =- 1;
    return true;
  } else if(curr.row + 1 < maxRows) {
    curr.row =+ 1;
    return true;
  }
  return false;
}

vector<pos> findAllPaths(vector<vector<int>> &m, pos start, pos end) {
  int maxCols = m.size();
  int maxRows = m[0].size();
  
  vector<pos> currPath;
  stack<pos> s;
  s.push(start);
  
  while(!s.empty()) {
    pos curr = s.top();
    s.pop();
    
    currPath.push_back(curr);
    
    cout << curr.row << ", " << curr.col << endl;
    cout << end.row << ", " << end.col << endl;
    
    if(curr == end) {
      break;
    }
    
    bool canMove = move(curr, maxCols, maxRows);
    if(canMove) {
      s.push(curr);
    }
  }
  
  return currPath;
}

void printMatrix(const vector<vector<int>> &m) {
  for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < m[i].size(); j++) {
      cout << m[i][j] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  // your code goes here
  
  vector<vector<int>> m = {{0,0,0,0,0,0,0,0},
                           {0,0,0,0,0,0,0,0},
                           {0,0,0,0,0,0,0,0}};
                              
    printMatrix(m);
  
    vector<pos> shortestP = findAllPaths(m, pos(0,0), pos(2,4));
    
    for_each(shortestP.begin(), shortestP.end(), [](pos curr){ cout << curr.row << ", " << curr.col << endl;});
    
  return 0;
}