#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

/*
Question: Question: 3 Sum Problem

Given an array, you have to find to find 3 parameters which sum up to 0.
a+b+c = 0
*/

typedef struct param_info {
	int a;
	int b;
	int c;
	param_info(int a_, int b_, int c_) : a(a_), b(b_), c(c_) {}
}param_info;

typedef struct pair_info {
	int a;
	int b;
	pair_info(int a_, int b_) : a(a_), b(b_) {}
}pair_info;

vector<param_info> three_sum(vector<int> &vec) {
	vector<param_info> parameters;
	unordered_map<int, vector<pair_info>> ht;

	for (int i = 0; i < vec.size() - 1; i++) {
		for (int j = i + 1; j < vec.size(); j++) {
			// store a + b into the hash table
			auto it = ht.find(vec[i] + vec[j]);

			if (it == ht.end()) {
				vector<pair_info> indices;
				indices.push_back(pair_info(vec[i], vec[j]));
				ht.insert(make_pair(vec[i] + vec[j], indices));
			}
			else {
				it->second.push_back(pair_info(vec[i], vec[j]));
			}
		}
	}

	for (int i = 0; i < vec.size(); i++) {
		// lookup for -c in the hash table, since a+b is stored
		// a + b + c = 0
		// a + b = -c
		auto it = ht.find(-vec[i]);

		if (it != ht.end()) {
			for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				parameters.push_back(param_info(it2->a, it2->b, vec[i]));
			}
		}
	}

	return parameters;
}

int main() {
	// your code goes here

	vector<int> vec = { 10, -8, 2, 5, -3, 4 };

	vector<param_info> parameters = three_sum(vec);

	for_each(parameters.begin(), parameters.end(), [](param_info p) { cout << "a: " << p.a << ", b: " << p.b << ", c: " << p.c << endl; });

	return 0;
}