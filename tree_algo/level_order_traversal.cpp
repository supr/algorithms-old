#include "bst.h"
using namespace std;

/*
Question: Binary Tree Level Order Traversal

Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
For example:
Given binary tree:
3
/ \
9  20
/ \
15  7

return its level order traversal as:
[
[3],
[9,20],
[15,7]
]
*/

class node_info {
public:
  Tree<int>::Node *curr;
  int depth;
  node_info(Tree<int>::Node *curr_, int depth_): curr(curr_), depth(depth_) {}
};

template <class T>
vector<vector<int>> Tree<T>::level_order_traversal(Tree<T>::Node *root) {
  std::queue<node_info> q;
  vector<vector<int>> nodes;
  vector<int> level_nodes;
  int depth_old = 0;
  q.push(node_info(root, 0));

  while (!q.empty()) {
    node_info n = q.front();
    q.pop();

    if (n.depth > depth_old) {
      nodes.push_back(level_nodes);
      level_nodes.clear();
      level_nodes.push_back(n.curr->value);
    }
    else {
      level_nodes.push_back(n.curr->value);
    }

    depth_old = n.depth;
    n.depth++;

    if (n.curr->left) {
      q.push(node_info(n.curr->left, n.depth));
    }
    if (n.curr->right) {
      q.push(node_info(n.curr->right, n.depth));
    }
  }

  nodes.push_back(level_nodes);
  return nodes;
}

int main() {
  Tree<int> t4;
  t4.insert(10);
  t4.insert(5);
  t4.insert(12);
  t4.insert(4);
  t4.insert(3);
  t4.insert(2);
  t4.insert(7);
  t4.insert(14);

  t4.print_head(t4, cout);

  vector<vector<int>> nodes = t4.level_order_traversal(t4.get_root());

  for (int i = 0; i < nodes.size(); i++) {
    for (int j = 0; j < nodes[i].size(); j++) {
      cout << nodes[i][j] << ' ';
    }

    cout << '\n';
  }

  return 0;
}
