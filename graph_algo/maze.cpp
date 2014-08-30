/*
Question: Rat in a Maze
Lets assume we have a rat maze as represented by the following NxM matrix 
where S is the start location and E is the end location. 

0 E 0 0 0 0 0 0 0
0 1 1 1 0 1 1 0 0
1 1 0 0 0 1 0 0 0
1 0 0 1 1 1 1 1 0
1 0 0 0 0 0 1 0 0
1 1 0 S 1 1 1 0 0
0 1 0 1 0 0 1 0 0
0 1 1 1 1 1 1 1 0
0 1 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 0 

0 Wall
E End
S Start
1 path

The idea (as with any rat maze) is to traverse from S to E. The matrix can 
have only 0 and 1 as values. 1 represents a path that can be taken and 0 
represents a blocked path. 

We can make the following assumption: 
S will always be (5,3) and E will always be (N,M). 

As seen from above, there can be many paths from S to E. 

How do we find the shortest (or longest) path from S to E without actually 
traversing all the possible paths. 

Please post (with proof/explantion) your algorithms. Also can you then think 
of ways to optimize the algo?
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

class Maze {
private:
  pos endPos;
  int max_row;
  int max_col;
  
  vector<vector<int>> matrix;
  vector<vector<int>> visited; 

private:
  bool isWall(const pos &p) {
    return matrix[p.row][p.col] == 0;
  }
  
  bool isValidPos(const pos &p) {
    if(p.row < 0 || p.row > max_row) {
      return false;
    }
    if(p.col < 0 || p.col > max_col) {
      return false;
    } 
    
    return true;
  }
  
public:
  Maze() {
    init();
  }
  
private:
  void init() {
     matrix = {{0,1,0,0,0,0,0,0,0},
               {0,1,1,1,0,1,1,0,0},
               {1,1,0,0,0,1,0,0,0},
               {1,0,0,1,1,1,1,1,0},
               {1,0,0,0,0,0,1,0,0},
               {1,1,0,1,1,1,1,0,0},
               {0,1,0,1,0,0,1,0,0},
               {0,1,1,1,1,1,1,0,0},
               {0,1,0,0,0,1,0,0,0},
               {0,0,0,0,0,0,0,0,0}};
                             
    max_col = matrix.size();
    max_row = matrix[0].size();
    
    visited.resize(max_row, vector<int>(max_col, 0));
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
    
    if(isWall(currPos + getNextStep(dir))) {
      return false;
    }
    
    return true;  
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

  void backtrack(vector<pos> &path, pos curr) {
    while (!path.empty()) {
      bool canDelete = true;
     
      vector<Direction> moveVec = {UP, DOWN, LEFT, RIGHT};
      for (auto m : moveVec) { 
        if (path.back() == (curr + getNextStep(m))) {
          canDelete = false;
        }
      }
      
      if (canDelete) {
        path.pop_back();  
      } else {
        break;
      }
    }
  }
  
  void cleanup(vector<pos> &path, pos curr) {
    for (auto it = path.rbegin(); it != path.rend(); it++) {
      if(*it == curr) {
        continue;
      }
      
      bool canDelete = true;
      
      vector<Direction> moveVec = {UP, DOWN, LEFT, RIGHT};
      for (auto m : moveVec) { 
        if (*it == (curr + getNextStep(m))) {
          canDelete = false;
        }
      }
      
      if (canDelete) {
        auto it2 = it++;
        path.erase(it.base());
        it = it2;
      } else {
        curr = *it;
      }
    }
  }
 
public: 
  void resetVisted() {
    for (int i = 0; i < visited.size(); i++) {
      for (int j = 0; j < visited[0].size(); j++) {
        visited[i][j] = 0;
      }
    }
  }
  
  // iterative BFS
  bool findPathBFS(const pos &startPos, const pos &endPos, vector<pos> &path) {
    pos currPos;
    queue<pos> q;
    q.push(startPos);
    
    while(!q.empty()) {
      currPos = q.front();  
      q.pop();
      
      if(currPos == endPos) {
        path.push_back(currPos);
        cleanup(path, currPos);
        return true;
      }
      
      if(!isVisited(currPos)) {
        setVisited(currPos);
      }
      else {
        continue;
      }
      
      path.push_back(currPos);
      
      bool moveSuccess = false;
      vector<Direction> moveVec = {UP, DOWN, LEFT, RIGHT};
    
      for (auto m : moveVec) {
        if(canMove(currPos, m)) {
          pos new_pos = move(currPos, m);
          q.push(new_pos);
          moveSuccess = true;
        }
      }
      
      if (!moveSuccess) {
        path.pop_back();
      }
    }
    
    return false;
  }

  // iterative DFS
  bool findPathDFS(const pos &startPos, const pos &endPos, vector<pos> &path) {
    pos currPos;
    stack<pos> q;
    q.push(startPos);
    
    while(!q.empty()) {
      currPos = q.top();  
      q.pop();
      
      backtrack(path, currPos);
      
      if(currPos == endPos) {
        path.push_back(currPos);
        return true;
      }
      
      if(!isVisited(currPos)) {
        setVisited(currPos);
      }
      else {
        continue;
      }
      
      path.push_back(currPos);
      
      bool moveSuccess = false;
      vector<Direction> moveVec = {UP, DOWN, LEFT, RIGHT};
    
      for (auto m : moveVec) {
        if(canMove(currPos, m)) {
          pos new_pos = move(currPos, m);
          q.push(new_pos);
          moveSuccess = true;
        }
      }
      
      if (!moveSuccess) {
        path.pop_back();
      }
    }
    
    return false;
  }
  
  bool findPathDFSRecur(const pos &startPos, const pos &endPos, vector<pos> &path) {
    pos currPos = startPos;
    return findPathDFSRecurInternal(startPos, endPos, currPos, path);
  }
  
  bool findPathDFSRecurInternal(const pos &startPos, const pos &endPos, pos &currPos, vector<pos> &path) {
    path.push_back(currPos);
    
    if (currPos == endPos) {
      cleanup(path, currPos);
      return true;
    }
    
    setVisited(currPos);
    
    vector<Direction> moveVec = {UP, DOWN, LEFT, RIGHT};
    for (auto m : moveVec) {
      if(canMove(currPos, m)) {
        pos newPos = move(currPos, m);
        if(!isVisited(newPos)) {
          return findPathDFSRecurInternal(startPos, endPos, newPos, path);
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
};


int main() {
  pos startPos = pos(5,3);
  pos endPos = pos(0,1);
  
  Maze m;
  
  vector<pos> path1;
  bool found1 = m.findPathDFS(startPos, endPos, path1);
  cout << "path found: " << found1 << endl;
  for_each(path1.begin(), path1.end(), [](pos curr) { cout << curr.row << "," << curr.col << " "; });
  
  m.resetVisted();
  
  vector<pos> path2;
  bool found2 = m.findPathBFS(startPos, endPos, path2);
  cout << "\npath found: " << found2 << endl;
  for_each(path2.begin(), path2.end(), [](pos curr) { cout << curr.row << "," << curr.col << " "; });

  m.resetVisted();
  vector<pos> path3;
  bool found3 = m.findPathDFSRecur(startPos, endPos, path3);
  cout << "\npath found: " << found3 << endl;
  for_each(path3.begin(), path3.end(), [](pos curr) { cout << curr.row << "," << curr.col << " "; });
  
  return 0;
}