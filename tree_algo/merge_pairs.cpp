#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

typedef struct node {
	int low;
	int high;
	node *left;
	node *right;
	node(int low_, int high_) : low(low_), high(high_), left(NULL), right(NULL) {}
}node;

class Range_tree {
private:
	node *root;

public:
	Range_tree() : root(NULL) {}

	void insert(int low, int high) {
		if (root == NULL) {
			node *n = new node(low, high);
			root = n;
		}
		else {
			node *curr = root;
			node *prev = root;

			while (curr) {
				if (curr->low > low) {
					prev = curr;
					curr = curr->left;
				}
				else if (curr->low < low) {
					prev = curr;
					curr = curr->right;
				}
				else {
					curr->high = high;
					break;
				}
			}

			if (!curr) {
				node *n = new node(low, high);

				if (prev->low > low) {
					prev->left = n;
				}
				else {
					prev->right = n;
				}
			}
		}
	}

	void insert_pairs(vector<pair<int, int>> &vec) {
		for (int i = 0; i < vec.size(); i++) {
			insert(vec[i].first, vec[i].second);
		}
	}

	void merge_ranges_internal(node *root, vector<pair<int,int>> &vec, int &curr_low, int &curr_high) {
		if (!root) {
			return;
		}

		merge_ranges_internal(root->left, vec, curr_low, curr_high);

		// no overlapp
		if (root->low > curr_high) {
			vec.push_back(make_pair(root->low, root->high));

			curr_low = root->low;
			curr_high = root->high;
		}
		// overlapp
		else {
			int index = vec.size() - 1;

			if (root->low <= vec[index].second) {
				if (root->high > vec[index].second) {
					vec[index].second = root->high;
				}
			}

			curr_low = vec[index].first;
			curr_high = vec[index].second;
		}

		merge_ranges_internal(root->right, vec, curr_low, curr_high);
	}

	vector<pair<int, int>> merge_ranges() {
		vector<pair<int, int>> pairs;

		int low = std::numeric_limits<int>::min();
		int high = std::numeric_limits<int>::min();
		merge_ranges_internal(root, pairs, low, high);

		return pairs;
	}
};

int main() {
	// your code goes here

	Range_tree rt1;
	vector<pair<int, int>> vec1 = { { 1, 2 }, { 3, 4 }, { 3, 6 }, { 8, 10 } };
	rt1.insert_pairs(vec1);
	vector<pair<int,int>> pairs1 = rt1.merge_ranges();
	for_each(pairs1.begin(), pairs1.end(), [](pair<int,int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt2;
	vector<pair<int, int>> vec2 = { { 1, 6 }, { 3, 4 }, { 3, 6 }, { 8, 10 } };
	rt2.insert_pairs(vec2);
	vector<pair<int, int>> pairs2 = rt2.merge_ranges();
	for_each(pairs2.begin(), pairs2.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt3;
	vector<pair<int, int>> vec3 = { { 1, 10 }, { 3, 4 }, { 3, 6 }, { 8, 10 } };
	rt3.insert_pairs(vec3);
	vector<pair<int, int>> pairs3 = rt3.merge_ranges();
	for_each(pairs3.begin(), pairs3.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt4;
	vector<pair<int, int>> vec4 = { { 0, 2 }, { 3, 4 }, { 1, 5 }, { 6, 8 } };
	rt4.insert_pairs(vec4);
	vector<pair<int, int>> pairs4 = rt4.merge_ranges();
	for_each(pairs4.begin(), pairs4.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt5;
	vector<pair<int, int>> vec5 = { { 0, 1 }, { 5, 6 } };
	rt5.insert_pairs(vec5);
	vector<pair<int, int>> pairs5 = rt5.merge_ranges();
	for_each(pairs5.begin(), pairs5.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt6;
	vector<pair<int, int>> vec6 = { { 1, 10 }, { 15, 20 }, { 12, 13 }, { 10, 12 }, { 19, 20 } };
	rt6.insert_pairs(vec6);
	vector<pair<int, int>> pairs6 = rt6.merge_ranges();
	for_each(pairs6.begin(), pairs6.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	return 0;
}