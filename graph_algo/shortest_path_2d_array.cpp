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
  NONE = 0,
  UP,
  DOWN,
  LEFT,
  RIGHT
} direction;

class pos {
public:
  int y;
  int x;
  pos(int r, int c): y(r), x(c) {}
  bool operator==(const pos &rhs) { 
    return y == rhs.y && x == rhs.x;
  }
  bool operator!=(const pos &rhs) { 
    return y != rhs.y || x != rhs.x;
  }
  pos &operator=(const pos &other) {
    if (this != &other) {
      y = other.x;
      x = other.y;    
    }

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
    cout << endl;
  }
  cout << endl;
}

int getMoveDir(const Direction &moveDir) {
  if (moveDir == LEFT || moveDir == UP) {
    return -1;
  } else if (moveDir == RIGHT || moveDir == DOWN) {
    return 1;
  }
}

bool checkBoundX(pos curr, const Direction &moveDir, int maxX) {
  if (((curr.x + getMoveDir(moveDir)) >= 0) && 
      ((curr.x + getMoveDir(moveDir)) < maxX)) {
    return true;
  } 
  return false;
}

bool checkBoundY(pos curr, const Direction &moveDir, int maxY) {
  if (((curr.y + getMoveDir(moveDir)) >= 0) && 
      ((curr.y + getMoveDir(moveDir)) < maxY)) {
    return true;
  }
  return false;
}

bool isCellVisited(pos curr, pos end, vector<vector<bool>> &visited) {
  if (end.x == curr.x && end.y == curr.y) {
    return false;
  }
  if (visited[curr.y][curr.x]) {
      return true;
    }
  visited[curr.y][curr.x] = true;
  return false;
}

bool doMove(pos &curr, const Direction &moveDir, int maxX, int maxY) {
  if ((moveDir == LEFT || moveDir == RIGHT) && checkBoundX(curr, moveDir, maxX)) {
    curr.x += getMoveDir(moveDir);
    return true;
  }
  if ((moveDir == UP || moveDir == DOWN) && checkBoundY(curr, moveDir, maxY)) {
    curr.y += getMoveDir(moveDir);
    return true;
  }
  return false;
}

bool checkMoveX(Direction &moveDir, pos curr, pos end, vector<vector<bool>> &visited) {
    if (curr.x != end.x) {
      if (curr.x < end.x) {
        moveDir = RIGHT;
      } else {
        moveDir = LEFT;
      }
      
      int nextMoveTo = getMoveDir(moveDir);
      if (!isCellVisited(curr + pos(nextMoveTo, 0), end, visited)) {
        return true; 
      }
    }
    return false;
}

bool checkMoveY(Direction &moveDir, pos curr, pos end, vector<vector<bool>> &visited) {
    if (curr.y != end.y) {
      if (curr.y < end.y) {
        moveDir = DOWN;
      } else {
        moveDir = UP;
      }
      
      int nextMoveTo = getMoveDir(moveDir);
      if (!isCellVisited(curr + pos(0, nextMoveTo), end, visited)) {
        return true; 
      }
    }
    return false;
}

bool getMoveDir(Direction &moveDir, pos curr, pos end, vector<vector<bool>> &visited) {
  if(checkMoveX(moveDir, curr, end, visited)) {
    return true;
  }
  if(checkMoveY(moveDir, curr, end, visited)) {
      return true;
    }
    return false;
}

void updateFailCount(bool canMove, int &moveFailedCount) {
  if (!canMove) {
      moveFailedCount++;
    } else {
      moveFailedCount = 0;
    }
}

vector<vector<pos>> findAllPaths(vector<vector<int>> &m, pos start, pos end) {
  vector<vector<pos>> totalPath;
  vector<vector<bool>> visited; 
  int maxY = m.size();
  int maxX = m[0].size();
  int moveFailedCount = 0;
  
  visited.resize(maxY, std::vector<bool>(maxX, false));
  
  while (true) {
    pos curr = start;
    vector<pos> currPath;
    
    while (curr != end) {
      Direction moveDir = NONE;
      bool canMove = getMoveDir(moveDir, curr, end, visited);
      
      updateFailCount(canMove, moveFailedCount);
      if (moveFailedCount != 0) {
        break;
      }
      
      doMove(curr, moveDir, maxX, maxY);  
      currPath.push_back(curr);
    }
    
    if (moveFailedCount == 2) {
      break;
    }
    
    if (curr == end) {
      totalPath.push_back(currPath);
    }
  }
  
  return totalPath;
}

int main() {
  // your code goes here
  
  vector<vector<int>> m = {{0,0,0,0,0,0,0,0},
                           {0,0,0,0,0,0,0,0},
                           {0,0,0,0,0,0,0,0}};
                              
  //printMatrix(m);
  
  vector<vector<pos>> shortestP = findAllPaths(m, pos(0,0), pos(2,4));
    
  for (int i = 0; i < shortestP.size(); i++) {
    for_each(shortestP[i].begin(), shortestP[i].end(), [](pos curr){ cout << curr.x << "," << curr.y << " ";});
    cout << endl;
  }
    
  return 0;
}