#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>
using namespace std;

// All edges must have nonnegative weights

//#define DEBUG_INFO
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
};

// find the shortest path from a start to a destination node
// keep a set of visited nodes
// select the node with the min. distance from Q
// if a new shortest path is found -> set new value of shortest path
vector<vertex_t> dijkstra(const adjacency_list_t &l, vertex_t src, vertex_t dst) {
  std::vector<weight_t> dist;
  std::vector<vertex_t> prev;
  std::priority_queue<edge, vector<edge>, comparison> q;

  // init dist, prev table  
  for (int i = 0; i < l.size(); i++) {
    dist.push_back(max_weight);
    prev.push_back(0);
  }
  dist[src] = 0;

  // insert into pqueue
  q.push(edge(src, dist[src]));

  while (!q.empty()) {
    edge u = q.top();
    q.pop();
  
    // loop for all edges connected to u
    for (auto v = l[u.target].begin(); v != l[u.target].end(); v++) {

      // The variable alt is the length of the path from the root node to the neighbor node v 
      // if it were to go through u. If this path is shorter than the current shortest path 
      // recorded for v, that current path is replaced with this alt path.

      int alt = dist[u.target] + v->weight; // accumulate shortest dist from source
  
      if (alt < dist[v->target]) {
        dist[v->target] = alt; // keep the shortest dist from src to v
        prev[v->target] = u.target;

        q.push(edge(v->target, dist[v->target])); // Add unvisited v into the Q to be processed  
      }
    }
  }

  #ifdef DEBUG_INFO
    print_dist(dist);
    print_prev(prev);
  #endif
    
  vector<vertex_t> shortestPath;
  vertex_t curr = dst;
  shortestPath.push_back(curr);
    
  while(curr != src) {
    curr = prev[curr];
    shortestPath.push_back(curr);
  }
    
  std::reverse(shortestPath.begin(), shortestPath.end());
    
  return shortestPath;
}

bool bellman_ford(const adjacency_list_t &l, vertex_t src) {
  std::vector<weight_t> dist;
  std::vector<vertex_t> prev;

  // init dist, prev table  
  for (int i = 0; i < l.size(); i++) {
    dist.push_back(max_weight);
    prev.push_back(0);
  }
  dist[src] = 0;

  for (int i = 0; i < l.size() - 1; i++) {
    for (int u = 0; u < l.size(); u++) {
      // loop for all edges connected to u
      for (auto v = l[u].begin(); v != l[u].end(); v++) {
        int alt = dist[u] + v->weight;

        if (alt < dist[v->target]) {
          dist[v->target] = alt;
          prev[v->target] = u;
        }
      }
    }
  }

  for (int u = 0; u < l.size(); u++) {

    // loop for all edges connected to u
    for (auto v = l[u].begin(); v != l[u].end(); v++) {
      int alt = dist[u] + v->weight;

      if (alt < dist[v->target]) {
        cout << "cycle detected" << '\n' << endl;
        return false; // graph contains negative cycle
      }
    }
  }

  return true;
}
  
int main() {
  // your code goes here

  /*
  // graph from: https://class.coursera.org/algo-2012-002/lecture/57
  // at 5:00min
      -----1-----
  (1)/     |     \(6)
    /      |      \
   0       |(2)    3
    \      |      /
  (4)\     |     /(3)
      -----2-----
  */

  cout << "Test graph with positive weights..." << endl;

  Graph g1;
  g1.addEdge(0, 1, 1);
  g1.addEdge(0, 2, 4);
  g1.addEdge(1, 0, 1);
  g1.addEdge(1, 2, 2);
  g1.addEdge(1, 3, 6);
  g1.addEdge(2, 0, 4);
  g1.addEdge(2, 1, 2);
  g1.addEdge(2, 3, 3);
  g1.addEdge(3, 1, 6);
  g1.addEdge(3, 2, 3);
  vector<vertex_t> shortestPath = dijkstra(g1.getAdjacencyList(), 0, 3);
  for (auto const& n : shortestPath) {
    cout << n << ' ';
  }

  cout << "Test graph with positive weights..." << endl;
  
  Graph g2;
  g2.addEdge(0, 1, 1);
  g2.addEdge(0, 2, 3);
  g2.addEdge(1, 0, 1);
  g2.addEdge(1, 2, 1);
  g2.addEdge(2, 1, 1);
  g2.addEdge(2, 0, 3);
  shortestPath = dijkstra(g2.getAdjacencyList(), 0, 2);
  for (auto const& n : shortestPath) {
    cout << n << ' ';
  }
  
  cout << "Test graph with negative weights..." << endl;

  Graph g3;
  g3.addEdge(0, 1, -1);
  g3.addEdge(0, 2, 3);
  g3.addEdge(1, 0, -1);
  g3.addEdge(1, 2, -1);
  g3.addEdge(2, 1, -1);
  g3.addEdge(2, 0, 3);
  cout << bellman_ford(g3.getAdjacencyList(), 0) << endl;
  
  cout << "Test graph with negative cycle..." << endl;
  
  Graph g4;
  g4.addEdge(0, 1, 1);
  g4.addEdge(0, 2, 1);
  g4.addEdge(0, 0, -3);
  g4.addEdge(0, 2, 1);
  g4.addEdge(0, 1, 1);
  g4.addEdge(0, 0, -3);
  
  cout << bellman_ford(g4.getAdjacencyList(), 0) << endl;
  
  return 0;
} 