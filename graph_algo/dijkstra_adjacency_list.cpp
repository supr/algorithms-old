#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>
using namespace std;

#define UNDIRECTED_GRAPH

typedef int vertex_t;
typedef double weight_t;
const weight_t max_weight = std::numeric_limits<double>::infinity();

typedef struct node {
	vertex_t target;
	weight_t weight;
	node(vertex_t arg_target, weight_t arg_weight) : target(arg_target), weight(arg_weight) {}
}node;

typedef struct comparison {
	bool operator()(const node &lhs, const node &rhs) {
		return lhs.weight < rhs.weight;
	}
}comparison;

typedef std::vector<std::vector<node>> adjacency_list_t;

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

void dijkstra(adjacency_list_t &l, vertex_t src, std::vector<weight_t> &dist, std::vector<vertex_t> &prev) {
	std::priority_queue<node, vector<node>, comparison> q;
#ifdef UNDIRECTED_GRAPH
	std::vector<bool> visited;
#endif

	// init dist, prev table	
	for (int i = 0; i < l.size(); i++) {
		dist.push_back(max_weight);
		prev.push_back(0);

#ifdef UNDIRECTED_GRAPH
		visited.push_back(false);
#endif
	}
	dist[src] = 0;

	// insert into pqueue
	q.push(node(dist[src], src));

	while (!q.empty()) {
		node u = q.top();
		q.pop();

#ifdef UNDIRECTED_GRAPH
		visited[u.target] = true;
#endif

		// loop for all edges connected to u
		for (auto v = l[u.target].begin(); v != l[u.target].end(); v++) {

			int alt = dist[u.target] + v->weight; // accumulate shortest dist from source

#ifdef UNDIRECTED_GRAPH
			if (!visited[v->target]) {
#endif
				if (alt < dist[v->target]) {
					dist[v->target] = alt; // keep the shortest dist from src to v
					prev[v->target] = u.target;

					q.push(node(v->target, dist[v->target])); // Add unvisited v into the Q to be processed  
				}
#ifdef UNDIRECTED_GRAPH
			}
#endif
		}
	}

	print_dist(dist);
	print_prev(prev);
}

bool bellman_ford(adjacency_list_t &l, vertex_t src, std::vector<weight_t> &dist, std::vector<vertex_t> &prev) {
#ifdef UNDIRECTED_GRAPH
	std::vector<bool> visited;
#endif	
	// init dist, prev table	
	for (int i = 0; i < l.size(); i++) {
		dist.push_back(max_weight);
		prev.push_back(0);
#ifdef UNDIRECTED_GRAPH
		visited.push_back(false);
#endif
	}
	dist[src] = 0;

	for (int i = 1; i < l.size() - 1; i++) {
		for (int u = 0; u < l.size(); u++) {
			// loop for all edges connected to u
			for (auto v = l[u].begin(); v != l[u].end(); v++) {
#ifdef UNDIRECTED_GRAPH
				if (!visited[v->target]) {
#endif
					int alt = dist[u] + v->weight;

					if (alt < dist[v->target]) {
						dist[v->target] = alt;
						prev[v->target] = u;
					}
#ifdef UNDIRECTED_GRAPH
				}
#endif
			}
		}

		for (int j = 0; j < l.size(); j++) {
#ifdef UNDIRECTED_GRAPH
			visited[j] = false;
#endif
		}
	}

	for (int u = 0; u < l.size(); u++) {
		// loop for all edges connected to u
		for (auto v = l[u].begin(); v != l[u].end(); v++) {
#ifdef UNDIRECTED_GRAPH
			if (!visited[v->target]) {
#endif
				int alt = dist[u] + v->weight;

				if (alt < dist[v->target]) {
					return false; // graph contains negative cycle
				}
#ifdef UNDIRECTED_GRAPH
			}
#endif
		}
	}

	print_dist(dist);
	print_prev(prev);

	return true;
}

int main() {
	// your code goes here

	adjacency_list_t adjacency_list(4);

	adjacency_list[0].push_back(node(1, 1));
	adjacency_list[0].push_back(node(2, 4));

	adjacency_list[1].push_back(node(0, 1));
	adjacency_list[1].push_back(node(2, 2));
	adjacency_list[1].push_back(node(3, 6));

	adjacency_list[2].push_back(node(0, 4));
	adjacency_list[2].push_back(node(1, 2));
	adjacency_list[2].push_back(node(3, 3));

	adjacency_list[3].push_back(node(1, 6));
	adjacency_list[3].push_back(node(2, 3));

	std::vector<weight_t> dist;
	std::vector<vertex_t> prev;

	dijkstra(adjacency_list, 0, dist, prev);

	std::vector<weight_t> dist2;
	std::vector<vertex_t> prev2;
	bellman_ford(adjacency_list, 0, dist2, prev2);

	return 0;
}