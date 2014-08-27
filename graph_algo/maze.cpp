/*
Question: Rat in a Maze
Lets assume we have a rat maze as represented by the following NxM matrix 
where S is the start location and E is the end location. 

0 E 0 0 0 0 0 0 0
0 1 1 1 0 1 1 0 0
0 1 0 1 0 1 0 0 0
0 0 0 1 1 1 1 1 0
0 0 0 0 0 0 1 0 0
0 1 0 S 1 1 1 0 0
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
using namespace std;

class pos {
public:
  int row;
  int col;
  pos(): row(0), col(0) {}
  pos(int row_, int col_): row(row_), col(col_) {}
  
  bool operator==(const pos &rhs) {
    return row == rhs.row && col == rhs.col;
  }
};

class Maze {
public:
  pos end_pos;
  int max_row;
  int max_col;
  
  vector<vector<int>> vec = {{0,1,0,0,0,0,0,0,0},
                             {0,1,1,1,0,1,1,0,0},
                             {0,1,0,1,0,1,0,0,0},
                             {0,0,0,1,1,1,1,1,0},
                             {0,0,0,0,0,0,1,0,0},
                             {0,1,0,1,1,1,1,0,0},
                             {0,1,0,1,0,0,1,0,0},
                             {0,1,1,1,1,1,1,0,0},
                             {0,1,0,0,0,1,0,0,0},
                             {0,0,0,0,0,0,0,0,0}};
                                  
  vector<vector<int>> visited = {{0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0}}; 

private:
  void setPos(const pos &p, char val) {
    vec[p.row][p.col] = val; 
  }
  
  char getPos(const int &row, const int &col) {
    return vec[row][col];
  }
  
  bool isValidPos(const int &row, const int &col) {
    if(row < 0 || row > max_row) {
      return false;
    }
    if(col < 0 || col > max_col) {
      return false;
    } 
    
    return true;
  }
  
public:
  Maze(const pos &init_end) {
    end_pos = init_end;
    
    max_col = vec.size();
    max_row = vec[0].size();
  }
  
  bool canMoveLeft(const pos &curr_pos) {
    if(!isValidPos(curr_pos.row, curr_pos.col - 1)) {
      return false;
    }
    
    if(getPos(curr_pos.row, curr_pos.col - 1) == 0) {
      return false;
    }
    
    return true;  
  }
  
  bool canMoveRight(const pos &curr_pos) {
    if(!isValidPos(curr_pos.row, curr_pos.col + 1)) {
      return false;
    }
    
    if(getPos(curr_pos.row, curr_pos.col + 1) == 0) {
      return false;
    }
    
    return true;  
  }

  bool canMoveUp(const pos &curr_pos) {
    if(!isValidPos(curr_pos.row - 1, curr_pos.col)) {
      return false;
    }
    
    if(getPos(curr_pos.row - 1, curr_pos.col) == 0) {
      return false;
    }
    
    return true;
  }
  
  bool canMoveDown(const pos &curr_pos) {
    if(!isValidPos(curr_pos.row + 1, curr_pos.col)) {
      return false;
    }
    
    if(getPos(curr_pos.row + 1, curr_pos.col) == 0) {
      return false;
    }
    
    return true;
  }
  
  void print() {
    for(int i = 0; i < vec.size(); i++) {
      for(int j = 0; j < vec[0].size(); j++) {
        cout << vec[i][j] << ' ';
      }
      cout << '\n';
    }
  }
  
  bool isVisited(const pos &p) {
    if(visited[p.row][p.col] == 0) {
      return false;
    }
    
    return true;
  }
  
  void setVisited(const pos &p, bool flag) {
    if(flag) {
      visited[p.row][p.col] = 1;
    }
    else {
      visited[p.row][p.col] = 0;
    }
  }
  
  pos moveLeft(const pos &curr_pos) {
    pos new_pos = curr_pos;
    new_pos.col -= 1; 
    return new_pos;
  }
  
  pos moveRight(const pos &curr_pos) {
    pos new_pos = curr_pos;
    new_pos.col += 1;
    return new_pos;
  }
  
  pos moveUp(const pos &curr_pos) {
    pos new_pos = curr_pos;
    new_pos.row -= 1;
    return new_pos;
  }
  
  pos moveDown(const pos &curr_pos) {
    pos new_pos = curr_pos;
    new_pos.row += 1;
    return new_pos;
  }
  
  void resetVisited() {
    for(int i = 0; i < visited.size(); i++) {
      for(int j = 0; j < visited[0].size(); j++) {
        visited[i][j] = 0;
      }
    }
  }

  // iterative DFS
  pos getExitIterative(const pos &start_pos) {
    pos tmp;
    stack<pos> q;
    q.push(start_pos);
    
    while(!q.empty()) {
      tmp = q.top();  
      q.pop();
      
      if(tmp == end_pos) {
        break;
      }
      
      if(!isVisited(tmp)) {
        setVisited(tmp, true);
      }
      else {
        continue;
      }
      
      if(canMoveDown(tmp)) {
        pos new_pos = moveDown(tmp);
        q.push(new_pos);
      }
      if(canMoveUp(tmp)) {
        pos new_pos = moveUp(tmp);
        q.push(new_pos);
      }
      if(canMoveLeft(tmp)) {
        pos new_pos = moveLeft(tmp);
        q.push(new_pos);
      }
      if(canMoveRight(tmp)) {
        pos new_pos = moveRight(tmp);
        q.push(new_pos);
      }
    }

    return tmp;
  }
  
  // recursive DFS
  pos getExitRecursive(pos curr_pos) {
    pos exit_pos;

    getExitRec(curr_pos, exit_pos);

    return exit_pos;
  }

  void getExitRec(pos curr_pos, pos &exit_pos) {
    if(curr_pos == end_pos) {
      exit_pos = curr_pos;
    }
    
    setVisited(curr_pos, true);
      
    if(canMoveDown(curr_pos)) {
      pos new_pos = moveDown(curr_pos);
      if(!isVisited(new_pos)) {
        getExitRec(new_pos, exit_pos);
      }
    }
    if(canMoveUp(curr_pos)) {
      pos new_pos = moveUp(curr_pos);
      if(!isVisited(new_pos)) {
        getExitRec(new_pos, exit_pos);
      }
    }
    if(canMoveRight(curr_pos)) {
      pos new_pos = moveRight(curr_pos);
      if(!isVisited(new_pos)) {
        getExitRec(new_pos, exit_pos);
      }
    }
    if(canMoveLeft(curr_pos)) {
      pos new_pos = moveLeft(curr_pos);
      if(!isVisited(new_pos)) {
        getExitRec(new_pos, exit_pos);
      }
    }
 }
};


int main() {
  Maze m(pos(0,1));
  
  m.print();
  
  pos start_pos = pos(5,3);
  pos exit_pos = m.getExitIterative(start_pos);
  cout << "exit_pos: " << exit_pos.row << ", " << exit_pos.col << endl;

  m.resetVisited();

  pos exit_pos2 = m.getExitRecursive(start_pos);
  cout << "exit_pos: " << exit_pos2.row << ", " << exit_pos2.col << endl;
  
  return 0;
}