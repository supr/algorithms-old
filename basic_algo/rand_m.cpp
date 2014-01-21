#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

/* Question:
Write a method to randomly generate a set of m integers from an array of size n.
Each element must have equal probability of being chosen.
*/

void shuffle(vector<int> &m_vec, int i) {
	if (i == 0) {
		return;
	}

	shuffle(m_vec, i - 1);

	int r = rand() % i;

	if (i < m_vec.size()) {
		swap(m_vec[i], m_vec[r]);
	}
}

vector<int> rand_m(vector<int> &n_vec, int m) {
	vector<int> m_vec;

	for (int i = 0; i < m; i++) {
		m_vec.push_back(n_vec[i]);
	}

	shuffle(m_vec, m);

	return m_vec;
}

int main() {
	// your code goes here

	srand(time(0));

	vector<int> n_vec = { 4, 2, 6, 8, 12, 14, 1, 5 };

	vector<int> m_vec = rand_m(n_vec, 5);
	for_each(m_vec.begin(), m_vec.end(), [](int value) { cout << value << ' ';  });

	return 0;
}