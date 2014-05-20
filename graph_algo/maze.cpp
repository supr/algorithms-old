/*
Question: Rat in a Maze
Given a 2d matrix and a start location (+), find the nearest exit location (#)
* There would be blockages at certain positions and they would be marked with =.
* You cannot go through those locations.
* Locations through which we can move are marked as o

Maze:
=#=======
=ooo=oo==
=o=o=o===
===ooooo=
======o==
=o=+ooo==
=o=o==o==
=ooooooo=
=o===o===
=========

= Wall
# End
+ Start
o path

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
  
  vector<vector<string>> vec = {{"=o======="},
                                {"=ooo=oo=="},
                                {"=o=o=o==="},
                                {"===ooooo="},
                                {"======o=="},
                                {"=o=oooo=="},
                                {"=o=o==o=="},
                                {"=ooooooo="},
                                {"=o===o==="},
                                {"========="}};
                                  
  vector<vector<string>> visited = {{"000000000"},
                                    {"000000000"},
                                    {"000000000"},
                                    {"000000000"},
                                    {"000000000"},
                                    {"000000000"},
                                    {"000000000"},
                                    {"000000000"},
                                    {"000000000"},
                                    {"000000000"}};                         

private:
  void set_pos(const pos &p, char val) {
    vec[p.row][0][p.col] = val; 
  }
  
  char get_pos(const int &row, const int &col) {
    return vec[row][0][col];
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
    max_row = vec[0][0].size();
  }
  
  bool getLeft(const pos &curr_pos) {
    if(is_valid_pos(curr_pos.row, curr_pos.col - 1) == false) {
      return false;
    }
    
    if(get_pos(curr_pos.row, curr_pos.col - 1) == '=') {
      return false;
    }
    
    return true;  
  }
  
  bool getRight(const pos &curr_pos) {
    if(is_valid_pos(curr_pos.row, curr_pos.col + 1) == false) {
      return false;
    }
    
    if(get_pos(curr_pos.row, curr_pos.col + 1) == '=') {
      return false;
    }
    
    return true;  
  }

  bool getUpper(const pos &curr_pos) {
    if(is_valid_pos(curr_pos.row - 1, curr_pos.col) == false) {
      return false;
    }
    
    if(get_pos(curr_pos.row - 1, curr_pos.col) == '=') {
      return false;
    }
    
    return true;
  }
  
  bool getLower(const pos &curr_pos) {
    if(is_valid_pos(curr_pos.row + 1, curr_pos.col) == false) {
      return false;
    }
    
    if(get_pos(curr_pos.row + 1, curr_pos.col) == '=') {
      return false;
    }
    
    return true;
  }
  
  void print() {
    for(int i = 0; i < vec.size(); i++) {
      cout << vec[i][0] << endl;
    }
  }
  
  bool is_visited(const pos &p) {
    if(visited[p.row][0][p.col] == '0') {
      return false;
    }
    else if(visited[p.row][0][p.col] == '1') {
      return true;
    }
  }
  
  void set_visited(const pos &p, bool flag) {
    if(flag) {
      visited[p.row][0][p.col] = '1';
    }
    else {
      visited[p.row][0][p.col] = '0';
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
  
  // iterative DFS
  pos get_exit(const pos &start_pos) {
    stack<pos> q;
    q.push(start_pos);
    
    while(!q.empty()) {
      pos tmp = q.top();  
      q.pop();
      
      if(tmp == end_pos) {
        return tmp;
      }
      
      if(!is_visited(tmp)) {
        set_visited(tmp, true);
      }
      else {
        continue;
      }
      
      if(getLower(tmp)) {
        pos n = move_lower(tmp);
        q.push(n);
      }
      if(getUpper(tmp)) {
        pos n = move_upper(tmp);
        q.push(n);
      }
      if(getLeft(tmp)) {
        pos n = move_left(tmp);
        q.push(n);
      }
      if(getRight(tmp)) {
        pos n = move_right(tmp);
        q.push(n);
      }
    }
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
  cout << exit_pos.row << ", " << exit_pos.col << endl;

  pos exit_pos2 = m.get_exit2(start_pos);
  cout << exit_pos2.row << ", " << exit_pos2.col << endl;
  
  return 0;
}