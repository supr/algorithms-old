#include <iostream>
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>
using namespace std;

//#define UNDIRECTED_GRAPH

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
		cout << "dist[" << i << "] = " << dist[i] << endl;
	}
}

void print_prev(std::vector<vertex_t> &prev) {
	for (int i = 0; i < prev.size(); i++) {
		cout << "prev[" << i << "] = " << prev[i] << endl;
	}
}

void BFS(adjacency_list_t &l, vertex_t src) {
	queue<vertex_t> s;
	vertex_t current = src;
	std::vector<bool> visited;

	for (int i = 0; i < l.size(); i++) {
		visited.push_back(false);
	}

	s.push(current);

	while (!s.empty()) {
		current = s.front();
		s.pop();

		if (!visited[current]) {
			cout << "current: " << current << endl;
			visited[current] = true;
		}

		for (auto it = l[current].begin(); it != l[current].end(); it++) {
			vertex_t neighbor = it->target;

			if (!visited[neighbor]) {
				s.push(neighbor);
			}
		}
	}
}

int main() {
	// your code goes here

	adjacency_list_t adjacency_list(8);

	adjacency_list[0].push_back(node(1, 5));
	adjacency_list[0].push_back(node(7, 8));
	adjacency_list[0].push_back(node(4, 9));

	adjacency_list[1].push_back(node(3, 15));
	adjacency_list[1].push_back(node(2, 12));
	adjacency_list[1].push_back(node(7, 4));

	adjacency_list[2].push_back(node(3, 3));
	adjacency_list[2].push_back(node(6, 11));

	adjacency_list[3].push_back(node(6, 9));

	adjacency_list[4].push_back(node(7, 5));
	adjacency_list[4].push_back(node(5, 4));
	adjacency_list[4].push_back(node(6, 20));

	adjacency_list[5].push_back(node(2, 1));
	adjacency_list[5].push_back(node(6, 13));

	adjacency_list[7].push_back(node(2, 7));
	adjacency_list[7].push_back(node(5, 6));

	BFS(adjacency_list, 0);

	return 0;
}