#include <unordered_map>

/* 
Question:
Clone a graph. Input is a Node pointer. Return the Node pointer of the cloned graph.

A graph is defined below:
struct Node {
vector neighbors;
}

reference: http://leetcode.com/2012/05/clone-graph-part-i.html

There are two main ways to traverse a graph: Breadth-first or Depth-first. 
Let's try the Breadth-first approach first, which requires a queue.

But, how do we know if a node has already been copied?
Easy, we could use a hash table! As we copy a node, we insert it into the table. 
If we later find that one of a node’s neighbor is already in the table, we do not 
make a copy of that neighbor, but to push its neighbor’s copy to its copy instead. 
Therefore, the hash table would need to store a mapping of key-value pairs, where 
the key is a node in the original graph and its value is the node’s copy.
*/

typedef unordered_map<Node *, Node *> Map;
 
Node *clone(Node *graph) {
  if (!graph) return NULL;
 
  Map map;
  queue<Node*> q;
  q.push(graph);
 
  Node *graphCopy = new Node();
  map[graph] = graphCopy;
 
  while (!q.empty()) {
    Node *node = q.front();
    q.pop();
    int n = node->neighbors.size();
    for (int i = 0; i < n; i++) {
      Node *neighbor = node->neighbors[i];
      // no copy exists
      if (map.find(neighbor) == map.end()) {
        Node *p = new Node();
        map[node]->neighbors.push_back(p);
        map[neighbor] = p;
        q.push(neighbor);
      } else {     // a copy already exists
        map[node]->neighbors.push_back(map[neighbor]);
      }
    }
  }
 
  return graphCopy;
}

Node *clone_graph_recursive(Node *node, unordered_map<Node*, Node*> &copied) {
  if(!node) {
    return NULL;
  }

  //First check if this node has already been copied
  unordered_map<Node*, Node*>::iterator it = copied.find(node);
  if(it!=copied.end()) {
    return it->second;
  }

  //If not, then create a copy of the node
  Node *new_node = new Node;
  new_node->data = node->data;

  //Add the copied node to the Hash table
  copied[node] = new_node;

  //Copy the node's neighbors using recursive calls
  for(int i = 0; i < node->neighbors.size(); i++) {
    new_node->neighbors.push_back(clone_graph_recursive(node->neighbors[i], copied));
  }

  return new_node;
}