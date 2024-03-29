#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

typedef int weight_t;
typedef int vertex_t;
const weight_t inf = numeric_limits<int>::max();

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

void bellman_ford(vector<vector<weight_t>> &matrix, vertex_t src, vertex_t dst) {
	vector<vertex_t> prev;
	vector<weight_t> dist;

	for (int i = 0; i < matrix.size(); i++) {
		prev.push_back(0);
		dist.push_back(inf);
	}
	dist[src] = 0;

	for (int i = 1; i < matrix.size() - 1; i++) {
		for (int u = 0; u < matrix.size(); u++) {
			for (int v = 0; v < matrix[u].size(); v++) {
				if (matrix[u][v] != inf) {
					int old = dist[u] + matrix[u][v];

					if (old < dist[v]) {
						dist[v] = old;
						prev[v] = u;
					}
				}
			}
		}
	}

	for (int u = 0; u < matrix.size(); u++) {
		for (int v = 0; v < matrix[u].size(); v++) {
			if (matrix[u][v] != inf) {
				int old = dist[u] + matrix[u][v];

				if (old < dist[v]) {
					cout << "cycle detected" << endl;
					return;
				}
			}
		}
	}

	print_dist(dist);
	print_prev(prev);
}

int main() {
	// your code goes here

	/* the graph is from the following lecture (at 5:00min): https://class.coursera.org/algo-2012-002/lecture/57

		-----2-----
	(1)/     |     \(6)
	  /      |      \
	 1       |(2)    --4
	  \      |      /
	(4)\     |     /(3)
	    -----3-----
	*/

	vector<vector<weight_t>> distance = { { 0, 1, 4, inf },
										  { 1, 0, 2, 6 },
		                                  { 4, 2, 0, 3 },
	                                      { inf, 6, 3, 0 } };

	bellman_ford(distance, 0, 2);

	return 0;
}