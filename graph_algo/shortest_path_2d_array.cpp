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
  UP = -1,
  DOWN = 1,
  LEFT = -1,
  RIGHT = 1
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

class moveDir {
public:
  int x;
  int y;
  moveDir(): x(0), y(0) {}
  moveDir &operator=(const moveDir &other) {
    if (this != &other) {
      y = other.y;
      x = other.x;    
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

bool checkBoundX(pos curr, moveDir mD, int maxX) {
  if (((curr.x + mD.x) >= 0) && ((curr.x + mD.x) < maxX)) {
    return true;
  } 
  return false;
}

bool checkBoundY(pos curr, moveDir mD, int maxY) {
  if (((curr.y + mD.y) >= 0) && ((curr.y + mD.y) < maxY)) {
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

bool doMove(pos &curr, moveDir mD, int maxX, int maxY) {
  if (mD.x != 0 && checkBoundX(curr, mD, maxX)) {
    curr.x += mD.x;
    return true;
  }
  if (mD.y != 0 && checkBoundY(curr, mD, maxY)) {
    curr.y += mD.y;
    return true;
  }
  return false;
}

bool checkMoveX(moveDir &mD, pos curr, pos end, vector<vector<bool>> &visited) {
    if (curr.x != end.x) {
      if (curr.x < end.x) {
        mD.x = RIGHT;
      } else {
        mD.x = LEFT;
      }
      
      if (!isCellVisited(curr + pos(mD.x, 0), end, visited)) {
        return true; 
      }
    }
    return false;
}

bool checkMoveY(moveDir &mD, pos curr, pos end, vector<vector<bool>> &visited) {
    if (curr.y != end.y) {
      if (curr.y < end.y) {
        mD.y = DOWN;
      } else {
        mD.y = UP;
      }
      
      if (!isCellVisited(curr + pos(0, mD.y), end, visited)) {
        return true; 
      }
    }
    return false;
}

bool getMoveDir(moveDir &mD, pos curr, pos end, vector<vector<bool>> &visited) {
  if(checkMoveX(mD, curr, end, visited)) {
    return true;
  }
  if(checkMoveY(mD, curr, end, visited)) {
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
      moveDir mD;
      
      bool canMove = getMoveDir(mD, curr, end, visited);
      
      updateFailCount(canMove, moveFailedCount);
      if (moveFailedCount != 0) {
        break;
      }
      
        doMove(curr, mD, maxX, maxY);
        
        //cout << curr.x << ", " << curr.y << endl;
        
      currPath.push_back(curr);
    }
    
    if (moveFailedCount == 2) {
      printMatrix(visited);
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