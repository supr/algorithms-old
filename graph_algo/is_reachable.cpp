#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>
using namespace std;

/*
Find if there is a path between two vertices in a directed graph
Given a Directed Graph and two vertices in it, check whether there 
is a path from the first given vertex to second. For example, in 
the following graph, there is a path from vertex 1 to 3. 
As another example, there is no path from 3 to 0.

Reference: http://www.geeksforgeeks.org/find-if-there-is-a-path-between-two-vertices-in-a-given-graph/
*/

typedef int vertex_t;
typedef double weight_t;
const weight_t max_weight = std::numeric_limits<double>::infinity();

struct edge {
  vertex_t target;
  weight_t weight;
  edge() = default;
  edge(vertex_t arg_target, weight_t arg_weight): target(arg_target), weight(arg_weight) {}
};

struct comparison {
  bool operator()(const edge &lhs, const edge &rhs) {
    return lhs.weight < rhs.weight;
  }
};

void print_dist(std::vector<weight_t> &dist) {
  for (int i = 0; i < dist.size(); i++) {
    cout << "dist[" << i << "] = " << dist[i] << ' ';
  }
  cout << '\n';
}

void print_prev(std::vector<vertex_t> &prev) {
  for (int i = 0; i < prev.size(); i++) {
    cout << "prev[" << i << "] = " << prev[i] << ' ';
  }
  cout << '\n';
}
  
typedef std::vector<std::vector<edge>> adjacency_list_t;

class Graph {
private:
  adjacency_list_t l;

public:
  adjacency_list_t &getAdjacencyList() {
    return l;
  }
  
  void addEdge(vertex_t src, vertex_t dst, weight_t weight) {
    if (max(src,dst) >= l.size()) {
      l.resize(max(src, dst) + 1);
    }
    
    l[src].push_back(edge(dst, weight));
  }
  
  void DFS(vertex_t start) {
    stack<edge> q;
    q.push(edge(start, 1));
    vector<bool> visited(3, false);
    
    while (!q.empty()) {
      edge curr = q.top();
      q.pop();
      
      if (visited[curr.target]) {
        continue;
      }
      else {
        visited[curr.target] = true;
      }
      
      cout << curr.target << endl;
      
      for (auto v = l[curr.target].begin(); v != l[curr.target].end(); v++) {
        q.push(edge(v->target, v->target));
      }
    }
  }
  
  bool isReachable(vertex_t u, vertex_t v) {
    stack<edge> q;
    q.push(edge(u, 1));
    vector<bool> visited(3, false);
    
    if (u == v) {
      return true;
    }
    
    while (!q.empty()) {
      edge curr = q.top();
      q.pop();
      
      if (visited[curr.target]) {
        continue;
      }
      else {
        visited[curr.target] = true;
      }
      
      if (curr.target == v) {
        return true;
      }
      
      for (auto v = l[curr.target].begin(); v != l[curr.target].end(); v++) {
        q.push(edge(v->target, v->target));
      }
    }
    
    return false;
  }
};

int main() {
  Graph g1;
  g1.addEdge(2, 0, 1);
  g1.addEdge(0, 2, 1);
  g1.addEdge(2, 3, 1);
  g1.addEdge(3, 3, 1);
  g1.addEdge(0, 1, 1);
  g1.addEdge(1, 2, 1);
  
  
  cout << g1.isReachable(1, 3) << endl;
  
  return 0;
} 