#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

/*
Given a matrix of MxN elements. Find the shortest path between a given source cell 
to a destination cell.
*/

enum Direction {
  NONE,
  UP,
  DOWN,
  LEFT,
  RIGHT
} direction;

class pos {
public:
  int y;
  int x;
  pos(int y_, int x_): y(y_), x(x_) {}
  bool operator==(const pos &rhs) { 
    return y == rhs.y && x == rhs.x;
  }
  bool operator!=(const pos &rhs) { 
    return !(y == rhs.y && x == rhs.x);
  }
  pos &operator=(pos other) {
    std::swap(x, other.x);
    std::swap(y, other.y);
    return *this;
  }
  pos &operator+(const pos &other) {
    if (this != &other) {
      y += other.x;
      x += other.y;   
    }
    return *this;
  }
};

template <typename T>
void printMatrix(const vector<vector<T>> &m) {
  for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < m[i].size(); j++) {
      cout << m[i][j] << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

int getNextMove(const Direction &move) {
  if (move == LEFT || move == UP) {
    return -1;
  } else if (move == RIGHT || move == DOWN) {
    return 1;
  }
}

bool checkBoundX(const pos &curr, int maxX) {
  if ((curr.x >= 0) && 
      (curr.x < maxX)) {
    return true;
  } 
  return false;
}

bool checkBoundY(const pos &curr, int maxY) {
  if ((curr.y >= 0) && 
      (curr.y < maxY)) {
    return true;
  }
  return false;
}

bool isValidPos(const pos &curr, int maxX, int maxY) {
  if (checkBoundX(curr, maxX) &&  checkBoundY(curr, maxY)) {
    return true;
  }
  return false;
}

void doMove(pos &curr, const Direction &move, int maxX, int maxY) {
  if (move == LEFT || move == RIGHT) {
    curr.x += getNextMove(move);
  } else if (move == UP || move == DOWN) {
    curr.y += getNextMove(move);
  }
}

bool canMoveX(Direction &move, const pos &curr, const pos &end) {
    if (curr.x != end.x) {
      if (curr.x < end.x) {
        move = RIGHT;
      } else {
        move = LEFT;
      }
      return true;
    }
    return false;
}

bool canMoveY(Direction &move, const pos &curr, const pos &end) {
    if (curr.y != end.y) {
      if (curr.y < end.y) {
        move = DOWN;
      } else {
        move = UP;
      }
      return true;
    }
    return false;
}

bool getNextMove(Direction &move, const pos &curr, const pos &end) {
  if(canMoveX(move, curr, end)) {
    return true;
  }
  else if(canMoveY(move, curr, end)) {
      return true;
  }
  return false;
}

bool findShortestPath(vector<vector<int>> &m, const pos &start, const pos &end, vector<pos> &currPath) {
  int maxY = m.size();
  int maxX = m[0].size();
  
  if (!isValidPos(start, maxX, maxY) || 
      !isValidPos(end, maxX, maxY)) {
    return false;
  }
  
  pos curr = start;
  currPath.push_back(curr);
  
  while (curr != end) {
    Direction move = NONE;
    
    bool canMove = getNextMove(move, curr, end);
    if (canMove == false) {
      return false;
    }
    
    doMove(curr, move, maxX, maxY);
    currPath.push_back(curr);
  }
  return true;
}

int main() {
  // your code goes here
  
  vector<vector<int>> m = {{0,0,0,0,0,0,0,0},
                           {0,0,0,0,0,0,0,0},
                           {0,0,0,0,0,0,0,0}};
  
  vector<pos> shortestPath;
    
  bool found = findShortestPath(m, pos(0,0), pos(2,4), shortestPath);
  if (!found) {
    cout << "invalid pos received" << endl;
    return 0;
  }  
  
  for_each(shortestPath.begin(), shortestPath.end(), [](pos curr){ cout << curr.x << "," << curr.y << " ";});
    
  return 0;
}