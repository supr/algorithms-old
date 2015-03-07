#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
Question:
Print an n-ary tree level by level

input:
    1
   / \
  2   3 
 /|\   \
4 5 6   7
   /|\\
  891011
       |
      12
      
output:
1 
2 3 
4 5 6 7 
8 9 10 11 
12 
*/

class Node {
public:
  int id;
  vector<Node*> neighbors;  // Undirected graph
  Node(int id_) : id(id_) {}

public:
  void set_neighbor(Node *n) {
    neighbors.push_back(n);
  }
};

void BFS(Node *start, int size) {
  class node_depth {
  public:
    int depth;
    Node *n;
    node_depth(int depth_, Node *n_): depth(depth_), n(n_) {}
  };
  
  int depth = 0;
  queue<node_depth> q;
  q.push(node_depth(depth, start));
  
  while (!q.empty()) {
    node_depth curr = q.front();
    q.pop();
    
    if (curr.depth > depth) {
      cout << '\n';
      depth++;
    }
    
    cout << curr.n->id << ' ';
    
    for (auto it = curr.n->neighbors.begin(); it != curr.n->neighbors.end(); it++) {
      q.push(node_depth(depth+1, *it));
    }
  }
}

int main() {
  // your code goes here

  Node node1(1);
  Node node2(2);
  Node node3(3);
  Node node4(4);
  Node node5(5);
  Node node6(6);
  Node node7(7);
  Node node8(8);
  Node node9(9);
  Node node10(10);
  Node node11(11);
  Node node12(12);
  
  node1.set_neighbor(&node2);
  node1.set_neighbor(&node3);

  node2.set_neighbor(&node4);
  node2.set_neighbor(&node5);
  node2.set_neighbor(&node6);

  node3.set_neighbor(&node7);

  node6.set_neighbor(&node8);
  node6.set_neighbor(&node9);
  node6.set_neighbor(&node10);
  node6.set_neighbor(&node11);
  
  node11.set_neighbor(&node12);
  
  BFS(&node1, 12);

  return 0;
}