#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

/* Question:
Given a set of time intervals in any order, merge all overlapping intervals into one and output the 
result which should have only mutually exclusive intervals. Let the intervals be represented as 
pairs of integers for simplicity.
For example, let the given set of intervals be {{1,3}, {2,4}, {5,7}, {6,8} }. The
intervals {1,3} and {2,4} overlap with each other, so they should be merged and become {1, 4}. 
Similarly {5, 7} and {6, 8} should be merged and become {5, 8}

Implementation: 
- Insertion: O(n * log(n))
- Merging: O(n)
*/

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

	void insert_intervals(vector<pair<int, int>> &vec) {
		for (int i = 0; i < vec.size(); i++) {
			insert(vec[i].first, vec[i].second);
		}
	}

	void merge_intervals_internal(node *root, vector<pair<int,int>> &vec, int &curr_low, int &curr_high) {
		if (!root) {
			return;
		}

		merge_intervals_internal(root->left, vec, curr_low, curr_high);

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

		merge_intervals_internal(root->right, vec, curr_low, curr_high);
	}

	vector<pair<int, int>> merge_intervals() {
		vector<pair<int, int>> intervals;

		int low = std::numeric_limits<int>::min();
		int high = std::numeric_limits<int>::min();
		merge_intervals_internal(root, intervals, low, high);

		return intervals;
	}
};

int main() {
	// your code goes here

	Range_tree rt1;
	vector<pair<int, int>> vec1 = { { 1, 2 }, { 3, 4 }, { 3, 6 }, { 8, 10 } };
	rt1.insert_intervals(vec1);
	vector<pair<int,int>> intervals1 = rt1.merge_intervals();
	for_each(intervals1.begin(), intervals1.end(), [](pair<int,int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt2;
	vector<pair<int, int>> vec2 = { { 1, 6 }, { 3, 4 }, { 3, 6 }, { 8, 10 } };
	rt2.insert_intervals(vec2);
	vector<pair<int, int>> intervals2 = rt2.merge_intervals();
	for_each(intervals2.begin(), intervals2.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt3;
	vector<pair<int, int>> vec3 = { { 1, 10 }, { 3, 4 }, { 3, 6 }, { 8, 10 } };
	rt3.insert_intervals(vec3);
	vector<pair<int, int>> intervals3 = rt3.merge_intervals();
	for_each(intervals3.begin(), intervals3.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt4;
	vector<pair<int, int>> vec4 = { { 0, 2 }, { 3, 4 }, { 1, 5 }, { 6, 8 } };
	rt4.insert_intervals(vec4);
	vector<pair<int, int>> intervals4 = rt4.merge_intervals();
	for_each(intervals4.begin(), intervals4.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt5;
	vector<pair<int, int>> vec5 = { { 0, 1 }, { 5, 6 } };
	rt5.insert_intervals(vec5);
	vector<pair<int, int>> intervals5 = rt5.merge_intervals();
	for_each(intervals5.begin(), intervals5.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	cout << '\n';

	Range_tree rt6;
	vector<pair<int, int>> vec6 = { { 1, 10 }, { 15, 20 }, { 12, 13 }, { 10, 12 }, { 19, 20 } };
	rt6.insert_intervals(vec6);
	vector<pair<int, int>> intervals6 = rt6.merge_intervals();
	for_each(intervals6.begin(), intervals6.end(), [](pair<int, int> p) { cout << p.first << ", " << p.second << endl;  });

	return 0;
}