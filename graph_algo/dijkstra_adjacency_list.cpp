#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>
using namespace std;

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

	// init dist, prev table	
	for (int i = 0; i < l.size(); i++) {
		dist.push_back(max_weight);
		prev.push_back(0);
	}
	dist[src] = 0;

	// insert into pqueue
	q.push(node(src, dist[src]));

	while (!q.empty()) {
		node u = q.top();
		q.pop();

		// loop for all edges connected to u
		for (auto v = l[u.target].begin(); v != l[u.target].end(); v++) {

			int alt = dist[u.target] + v->weight; // accumulate shortest dist from source

			if (alt < dist[v->target]) {
				dist[v->target] = alt; // keep the shortest dist from src to v
				prev[v->target] = u.target;

				q.push(node(v->target, dist[v->target])); // Add unvisited v into the Q to be processed  
			}
		}
	}

	print_dist(dist);
	print_prev(prev);
	cout << '\n';
}

bool bellman_ford(adjacency_list_t &l, vertex_t src, std::vector<weight_t> &dist, std::vector<vertex_t> &prev) {
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

	print_dist(dist);
	print_prev(prev);
	cout << '\n';

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
	0       |(2)    --3
	\      |      /
	(4)\     |     /(3)
	-----2-----
	*/

	cout << "Test graph with positive weights..." << endl;

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

	std::vector<weight_t> dist1;
	std::vector<vertex_t> prev1;
	dijkstra(adjacency_list, 0, dist1, prev1);

	std::vector<weight_t> dist2;
	std::vector<vertex_t> prev2;
	bellman_ford(adjacency_list, 0, dist2, prev2);

	cout << "Test graph with positive weights..." << endl;

	adjacency_list_t adjacency_list2(3);

	adjacency_list2[0].push_back(node(1, 1));
	adjacency_list2[0].push_back(node(2, 3));

	adjacency_list2[1].push_back(node(0, 1));
	adjacency_list2[1].push_back(node(2, 1));

	adjacency_list2[2].push_back(node(1, 1));
	adjacency_list2[2].push_back(node(0, 3));

	dist1.clear();
	prev1.clear();
	dijkstra(adjacency_list2, 0, dist1, prev1);

	dist2.clear();
	prev2.clear();
	bellman_ford(adjacency_list2, 0, dist2, prev2);

	cout << "Test graph with negative weights..." << endl;

	adjacency_list_t adjacency_list3(3);

	adjacency_list3[0].push_back(node(1, -1));
	adjacency_list3[0].push_back(node(2, 3));

	adjacency_list3[1].push_back(node(0, -1));
	adjacency_list3[1].push_back(node(2, -1));

	adjacency_list3[2].push_back(node(1, -1));
	adjacency_list3[2].push_back(node(0, 3));

	//dist1.clear();
	//prev1.clear();
	//dijkstra(adjacency_list3, 0, dist1, prev1);

	dist2.clear();
	prev2.clear();
	bellman_ford(adjacency_list3, 0, dist2, prev2);

	cout << "Test graph with negative cycle..." << endl;

	adjacency_list_t adjacency_list4(3);

	adjacency_list4[0].push_back(node(1, 1));
	adjacency_list4[0].push_back(node(2, 1));

	adjacency_list4[1].push_back(node(0, -3));
	adjacency_list4[1].push_back(node(2, 1));

	adjacency_list4[2].push_back(node(1, 1));
	adjacency_list4[2].push_back(node(0, -3));

	//dist1.clear();
	//prev1.clear();
	//dijkstra(adjacency_list4, 0, dist1, prev1);

	dist2.clear();
	prev2.clear();
	bellman_ford(adjacency_list4, 0, dist2, prev2);

	return 0;
}