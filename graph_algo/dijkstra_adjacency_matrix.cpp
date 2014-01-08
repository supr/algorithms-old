#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

typedef int weight_t;
typedef int vertex_t;
const weight_t inf = numeric_limits<int>::max();

typedef struct node {
	vertex_t vertex;
	weight_t weight;
	node(vertex_t vertex_t, weight_t weight_) : vertex(vertex_t), weight(weight_) {}
}node;

typedef struct compare {
	bool operator()(const node lhs, const node rhs) {
		return lhs.weight < rhs.weight;
	}
}compare;

void print_dist(vector<weight_t> &dist) {
	for (int i = 0; i < dist.size(); i++) {
		cout << dist[i] << ' ';
	}
	cout << '\n';
}

void print_prev(vector<vertex_t> &prev) {
	for (int i = 0; i < prev.size(); i++) {
		cout << prev[i] << ' ';
	}
	cout << '\n';
}

void dijkstra(vector<vector<weight_t>> &matrix, vertex_t src, vertex_t dst) {
	priority_queue<node, vector<node>, compare> q;
	vector<weight_t> prev;
	vector<vertex_t> dist;

	for (int i = 0; i < matrix.size(); i++) {
		prev.push_back(0);
		dist.push_back(inf);
	}
	dist[src] = 0;

	q.push(node(src, dist[src]));

	while (!q.empty()) {
		node u = q.top();
		q.pop();

		// loop over all neighbors connected
		for (int v = 0; v < matrix[u.vertex].size(); v++) {
			if (matrix[u.vertex][v] != inf) {
				int old = dist[u.vertex] + matrix[u.vertex][v]; // accumulate shortest dist from source

				if (old < dist[v]) {
					dist[v] = old; // keep the shortest dist from src to v
					prev[v] = u.vertex;

					q.push(node(v, dist[v])); // Add unvisited v into the Q to be processed
				}
			}
		}
	}

	print_dist(dist);
	print_prev(prev);
}

int main() {
	// your code goes here

	//s = 0
	//v = 1
	//w = 2
	//t = 3

	// graph from: https://class.coursera.org/algo-2012-002/lecture/57
	// at 5:00min
	vector<vector<weight_t>> distance = { { 0, 1, 4, inf },
	{ inf, 0, 2, 6 },
	{ inf, inf, 0, 3 },
	{ inf, inf, inf, 0 } };

	dijkstra(distance, 0, 2);

	return 0;
}