/*
Question:
(http://www.geeksforgeeks.org/find-number-of-islands/)
Given a 2-D array of 0s and 1s, find islands in it. 
An Island is 1s together. 0 = water, 1 = land
E.g (below there is U shaped island)
{1, 1, 0, 0, 0},
{0, 1, 0, 0, 1},
{1, 0, 0, 1, 1},
{0, 0, 0, 0, 0},
{1, 0, 1, 0, 1}

Find the number of connected islands
Find the largest connected island
*/

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

enum Direction {
  NONE,
  UP,
  DOWN,
  LEFT,
  RIGHT
} direction;

class pos {
public:
  int row;
  int col;
  pos(): row(0), col(0) {}
  pos(int row_, int col_): row(row_), col(col_) {}
  bool operator==(const pos &rhs) {
    return row == rhs.row && col == rhs.col;
  }
  bool operator!=(const pos &rhs) {
    return !(row == rhs.row && col == rhs.col);
  }
  pos operator+(const pos &rhs) {
    pos tmp(row, col);
    tmp.row += rhs.row;
    tmp.col += rhs.col;
    return tmp;
  }
  pos &operator+=(const pos &rhs) {
    row += rhs.row;
    col += rhs.col;
    return *this;
  }
  pos operator-(const pos &rhs) {
    pos tmp(row, col);
    tmp.row -= rhs.row;
    tmp.col -= rhs.col;
    return tmp;
  }
};

class Islands {
private:
  int numRows;
  int numCols;
  
  vector<vector<int>> matrix;
  vector<vector<int>> visited; 

private:  
  bool isValidPos(const pos &p) {
    if(p.row < 0 || p.row >= numRows) {
      return false;
    }
    if(p.col < 0 || p.col >= numCols) {
      return false;
    } 
    
    return true;
  }
  
  void init() {
    matrix = {{1, 1, 0, 0, 0},
              {0, 1, 0, 0, 1},
              {1, 0, 0, 1, 1},
              {0, 0, 0, 0, 0},
              {1, 0, 1, 0, 1}};
                             
    numCols = matrix.size();
    numRows = matrix[0].size();
    
    visited.resize(numRows, vector<int>(numCols, 0));
  }
  
  pos getNextStep(const Direction &dir) {
    if (dir == UP) { 
      return pos(-1,0); 
    }
    else if (dir == LEFT) {
      return pos(0,-1);
    } 
    else if (dir == DOWN) {
      return pos(1,0);
    }
    else if (dir == RIGHT) {
      return pos(0,1);  
    }
  }
  
  bool canMove(pos currPos, const Direction &dir) {
    if(!isValidPos(currPos + getNextStep(dir))) {
      return false;
    }

    if (isIsland(currPos + getNextStep(dir))) {
      return true;
    }

    return false;  
  }
  
  bool isVisited(const pos &p) {
    if(visited[p.row][p.col] == 0) {
      return false;
    }
    
    return true;
  }
  
  void setVisited(const pos &p) {
    visited[p.row][p.col] = 1;
  }
  
  pos move(const pos &currPos, const Direction &dir) {
    pos new_pos = currPos;
    new_pos += getNextStep(dir); 
    return new_pos;
  }
 
  bool isIsland(const pos &currPos) {
    return matrix[currPos.row][currPos.col] == 1;
  }
  
public:
  Islands() {
    init();
  }

  int countIslands() {
    int count = 0;
    
    for (int row = 0; row < numRows; row++) {
      for (int col = 0; col < numCols; col++) {
        pos currPos = pos(row, col);
        
        if (isIsland(currPos) && !isVisited(currPos)) {
          count++;
          findCompleteIslandDFS(currPos);
        }
      }
    }
    
    return count;
  }

  void findCompleteIslandDFS(const pos &start) {
    pos currPos = start;
    queue<pos> q;
    q.push(currPos);
    
    while (!q.empty()) {
      currPos = q.front();
      q.pop();
      
      if (!isVisited(currPos)) {
        setVisited(currPos);
      } else {
        continue;
      }

      vector<Direction> moveDirs = {LEFT, RIGHT, UP, DOWN};
      for (auto m : moveDirs) {
        if (canMove(currPos, m)) {
          pos newPos = move(currPos, m);
          q.push(newPos);
        }
      }
    }
  }
  
  void print() {
    for(int i = 0; i < matrix.size(); i++) {
      for(int j = 0; j < matrix[0].size(); j++) {
        cout << matrix[i][j] << ' ';
      }
      cout << '\n';
    }
  }

  void resetVisted() {
    for (int i = 0; i < visited.size(); i++) {
      for (int j = 0; j < visited[0].size(); j++) {
        visited[i][j] = 0;
      }
    }
  }
};


int main() {
  Islands i;
  
  int numIslands = i.countIslands();
  cout << "\nIslands found: " << numIslands << endl;

  //m.resetVisted();
  
  return 0;
}