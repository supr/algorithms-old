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

//#define undirected_graph

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
  
  void addEdge(vertex_t src, vertex_t dst, weight_t weight=0) {
    if (max(src,dst) >= l.size()) {
      l.resize(max(src, dst) + 1);
    }
    
#ifdef undirected_graph    
    l[src].push_back(edge(dst, 0));
    l[dst].push_back(edge(src, 0));
#else
  l[src].push_back(edge(dst, weight));
#endif
  }
  
  bool has_cycle_undirected() {
    // Mark all the vertices as not visited and not part of recursion stack
    vector<bool> visited(l.size(), false);
    
    // Call the recursive helper function to detect cycle in different DFS trees
    for (int i = 0; i < l.size(); i++) {
      if (!visited[i]) { // Don't recur for u if it is already visited
        if (has_cycle_undirected_util(i, visited, -1)) {
          return true;
        }
      }
    }
    
    return false;
  }
  
  // A recursive function that uses visited[] and parent to detect
  // cycle in subgraph reachable from vertex v.
  bool has_cycle_undirected_util(vertex_t u, vector<bool> &visited, vertex_t parent) {
    // Mark the current node as visited
  visited[u] = true;
  
  // Recur for all the vertices adjacent to this vertex
  for (auto v = l[u].begin(); v != l[u].end(); v++) {
    // If an adjacent is not visited, then recur for that adjacent
    if (!visited[v->target]) {
      if (has_cycle_undirected_util(v->target, visited, u)) {
        return true;
      }
    }
    // If an adjacent is visited and not parent of current vertex,
        // then there is a cycle.
    else if (v->target != parent) {
      return true;
    }
  }
  
  return false;
  }
  
  // To detect cycle, we can check for cycle in individual trees by checking back edges.
  // To detect a back edge, we can keep track of vertices currently in recursion 
  // stack of function for DFS traversal. If we reach a vertex that is already in 
  // the recursion stack, then there is a cycle in the tree. The edge that connects 
  // current vertex to the vertex in the recursion stack is back edge. We have used 
  // rec[] array to keep track of vertices in the recursion stack.
  bool has_cycle_directed() {
    // Mark all the vertices as not visited and not part of recursion stack
    vector<bool> visited(l.size(), false);
    vector<bool> rec(l.size(), false);
    
    // Call the recursive helper function to detect cycle in different DFS trees
    for (int i = 0; i < l.size(); i++) {
      if (has_cycle_directed_util(i, visited, rec)) {
        return true;
      }
    }
    
    return false;
  }
  
  bool has_cycle_directed_util(vertex_t u, vector<bool> visited, vector<bool> &rec) {
    if(visited[u] == false) {
        // Mark the current node as visited and part of recursion stack
        visited[u] = true;
        rec[u] = true;
 
        // Recur for all the vertices adjacent to this vertex
        for(auto v = l[u].begin(); v != l[u].end(); v++) {
            if (!visited[v->target] && has_cycle_directed_util(v->target, visited, rec)) {
                return true;
            }
            else if (rec[v->target]) {
                return true;
            }
        }
 
    }
    
    rec[u] = false;  // remove the vertex from recursion stack
    return false;
  }
};

int main() {
#ifdef undirected_graph
  Graph g1;
  g1.addEdge(1, 0);
  g1.addEdge(0, 2);
  g1.addEdge(2, 0);
  g1.addEdge(0, 3);
  g1.addEdge(3, 4);
  g1.has_cycle_undirected() ? cout << "Graph contains cycle\n" :
                              cout << "Graph doesn't contain cycle\n";
  
  Graph g2;
  g2.addEdge(0, 1);
  g2.addEdge(1, 2);
  g2.has_cycle_undirected() ? cout << "Graph contains cycle\n" :
                              cout << "Graph doesn't contain cycle\n";
#else

  Graph g3;
  g3.addEdge(0, 1, 1);
  g3.addEdge(0, 2, 1);
  g3.addEdge(1, 2, 1);
  g3.addEdge(2, 0, 1);
  g3.addEdge(2, 3, 1);
  g3.addEdge(3, 3, 1);
  g3.has_cycle_directed() ? cout << "Graph contains cycle\n" :
                            cout << "Graph doesn't contain cycle\n";
#endif

  return 0;
}