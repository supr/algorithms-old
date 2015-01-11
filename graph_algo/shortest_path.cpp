#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
Question: Given an undirected graph with the following Node class. Find the shortest path to the destination node. There is
only a unique path to the destination, which is indicated with is_exit.
*/

class Node {
public:
  int id;
  char x; // "X" or "O" where "X" means blocked while "O" otherwise.
  bool is_exit;
  vector<Node*> neighbors;  // Undirected graph
  Node(int id_, char x_, bool is_exit_) : id(id_), x(x_), is_exit(is_exit_) {}

public:
  void set_neighbor(Node *n) {
    neighbors.push_back(n);
  }
};

vector<Node*> ShortestPath(Node *start, int size) {
  queue<Node*> q;
  vector<bool> visited;
  vector<Node*> shortest_path;

  for (int i = 0; i < size; i++) {
    visited.push_back(false);
  }

  q.push(start);

  while (!q.empty()) {
    Node *u = q.front();
    q.pop();

    int node_index = u->id - 1; // visited stores node ids from pos 0 to id.size()-1
    if (!visited[node_index]) {
      visited[node_index] = true;
    } else {
      continue;
    }

    shortest_path.push_back(u);
    
    if (u->is_exit) {
      break;
    }

    for (auto it = u->neighbors.begin(); it != u->neighbors.end(); it++) {
      if ((*it)->x == 'O') {
        q.push(*it);
      }
    }
  }

  return shortest_path;
}

int main() {
  // your code goes here

  Node node1(1, 'O', false);
  Node node2(2, 'O', false);
  Node node3(3, 'X', false);
  Node node4(4, 'O', true);

  node1.set_neighbor(&node2);
  node1.set_neighbor(&node3);

  node2.set_neighbor(&node1);
  node2.set_neighbor(&node3);
  node2.set_neighbor(&node4);

  node3.set_neighbor(&node1);
  node3.set_neighbor(&node2);
  node3.set_neighbor(&node4);

  node4.set_neighbor(&node2);
  node4.set_neighbor(&node3);

  vector<Node*> shortest_path = ShortestPath(&node1, 4); // 4 nodes in the graph

  for_each(shortest_path.begin(), shortest_path.end(), [](Node *n){ cout << n->id << endl; });

  return 0;
}