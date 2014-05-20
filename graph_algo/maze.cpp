/*
Question: Rat in a Maze
Lets assume we have a rat maze as represented by the following NxM matrix 
where S is the start location and F is the end location. 

0 F 0 0 0 0 0 0 0
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
# End
+ Start
1 path

The idea (as with any rat maze) is to traverse from S to F. The matrix can 
have only 0 and 1 as values. 1 represents a path that can be taken and 0 
represents a blocked path. 

We can make the following assumption: 
S will always be (5,3) and F will always be (N,M). 

As seen from above, there can be many paths from S to F. 

How do we find the shortest (or longest) path from S to F without actually 
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
  void set_pos(const pos &p, char val) {
    vec[p.row][p.col] = val; 
  }
  
  char get_pos(const int &row, const int &col) {
    return vec[row][col];
  }
  
  bool is_valid_pos(const int &row, const int &col) {
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
  
  bool getLeft(const pos &curr_pos) {
    if(is_valid_pos(curr_pos.row, curr_pos.col - 1) == false) {
      return false;
    }
    
    if(get_pos(curr_pos.row, curr_pos.col - 1) == 0) {
      return false;
    }
    
    return true;  
  }
  
  bool getRight(const pos &curr_pos) {
    if(is_valid_pos(curr_pos.row, curr_pos.col + 1) == false) {
      return false;
    }
    
    if(get_pos(curr_pos.row, curr_pos.col + 1) == 0) {
      return false;
    }
    
    return true;  
  }

  bool getUpper(const pos &curr_pos) {
    if(is_valid_pos(curr_pos.row - 1, curr_pos.col) == false) {
      return false;
    }
    
    if(get_pos(curr_pos.row - 1, curr_pos.col) == 0) {
      return false;
    }
    
    return true;
  }
  
  bool getLower(const pos &curr_pos) {
    if(is_valid_pos(curr_pos.row + 1, curr_pos.col) == false) {
      return false;
    }
    
    if(get_pos(curr_pos.row + 1, curr_pos.col) == 0) {
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
  
  bool is_visited(const pos &p) {
    if(visited[p.row][p.col] == 0) {
      return false;
    }
    
    return true;
  }
  
  void set_visited(const pos &p, bool flag) {
    if(flag) {
      visited[p.row][p.col] = 1;
    }
    else {
      visited[p.row][p.col] = 0;
    }
  }
  
  pos move_left(const pos &curr_pos) {
    pos new_pos = curr_pos;
    new_pos.col -= 1; 
    return new_pos;
  }
  
  pos move_right(const pos &curr_pos) {
    pos new_pos = curr_pos;
    new_pos.col += 1;
    return new_pos;
  }
  
  pos move_upper(const pos &curr_pos) {
    pos new_pos = curr_pos;
    new_pos.row -= 1;
    return new_pos;
  }
  
  pos move_lower(const pos &curr_pos) {
    pos new_pos = curr_pos;
    new_pos.row += 1;
    return new_pos;
  }
  
  void reset_visited() {
    for(int i = 0; i < visited.size(); i++) {
      for(int j = 0; j < visited[0].size(); j++) {
        visited[i][j] = 0;
      }
    }
  }

  // iterative DFS
  pos get_exit(const pos &start_pos) {
    pos tmp;
    stack<pos> q;
    q.push(start_pos);
    
    while(!q.empty()) {
      tmp = q.top();  
      q.pop();
      
      if(tmp == end_pos) {
        break;
      }
      
      if(!is_visited(tmp)) {
        set_visited(tmp, true);
      }
      else {
        continue;
      }
      
      if(getLower(tmp)) {
        pos new_pos = move_lower(tmp);
        q.push(new_pos);
      }
      if(getUpper(tmp)) {
        pos new_pos = move_upper(tmp);
        q.push(new_pos);
      }
      if(getLeft(tmp)) {
        pos new_pos = move_left(tmp);
        q.push(new_pos);
      }
      if(getRight(tmp)) {
        pos new_pos = move_right(tmp);
        q.push(new_pos);
      }
    }

    return tmp;
  }
    
  // recursive DFS
  pos get_exit2(pos curr_pos) {
    if(curr_pos == end_pos) {
      return curr_pos;
    }
    
    set_visited(curr_pos, true);
      
    if(getLower(curr_pos)) {
      pos new_pos = move_lower(curr_pos);
      if(!is_visited(new_pos)) {
        get_exit2(new_pos);
      }
    }
    if(getUpper(curr_pos)) {
      pos new_pos = move_upper(curr_pos);
      if(!is_visited(new_pos)) {
        get_exit2(new_pos);
      }
    }
    if(getRight(curr_pos)) {
      pos new_pos = move_right(curr_pos);
      if(!is_visited(new_pos)) {
        get_exit2(new_pos);
      }
    }
    if(getLeft(curr_pos)) {
      pos new_pos = move_left(curr_pos);
      if(!is_visited(new_pos)) {
        get_exit2(new_pos);
      }
    }
 }
};


int main() {
  Maze m(pos(0,1));
  
  m.print();
  
  pos start_pos = pos(5,3);
  pos exit_pos = m.get_exit(start_pos);
  cout << "exit_pos: " << exit_pos.row << ", " << exit_pos.col << endl;

  m.reset_visited();

  pos exit_pos2 = m.get_exit2(start_pos);
  cout << "exit_pos: " << exit_pos2.row << ", " << exit_pos2.col << endl;
  
  return 0;
}