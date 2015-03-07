#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

/*
Question:
Print all paths from a given source to a destination
Given a directed graph, a source vertex ‘s’ and a destination vertex ‘d’, print all 
paths from given ‘s’ to ‘d’.

Consider the following directed graph. Let the s be 2 and d be 3. There are 4 different 
paths from 2 to 3.
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
  
  vector<vector<vertex_t>> find_all_paths(vertex_t src, vertex_t dst) {
    vector<bool> visited(l.size(), false);
    vector<vector<vertex_t>> all_paths;
    vector<vertex_t> path;
    
    print_all_paths_util(src, dst, visited, path, all_paths);
    
    return all_paths;
  }
  
  void print_all_paths_util(vertex_t u, vertex_t dst, vector<bool> &visited, vector<vertex_t> &path, vector<vector<vertex_t>> &all_paths) {
    path.push_back(u);
    
    if (u == dst) {
      all_paths.push_back(path);
    }
    else {
      for (auto v = l[u].begin(); v != l[u].end(); v++) {
        if (visited[v->target]) {
          continue;
        }
        else {
          visited[v->target] = true;
        }
        
        print_all_paths_util(v->target, dst, visited, path, all_paths);
      }
    }
    
    path.pop_back();
    visited[u] = false;
  }
};

int main() {
  Graph g1;
  g1.addEdge(0, 1, 1);
  g1.addEdge(0, 2, 1);
  g1.addEdge(0, 3, 1);
  g1.addEdge(2, 0, 1);
  g1.addEdge(2, 1, 1);
  g1.addEdge(1, 3, 1);
  
  vector<vector<vertex_t>> paths = g1.find_all_paths(2, 3);
  
  for (auto it = paths.begin(); it != paths.end(); it++) {
    for (auto it2 = it->begin(); it2 != it->end(); it2++) {
      cout << *it2 << ' ';
    }
    cout << '\n';
  } 
  
  return 0;
}