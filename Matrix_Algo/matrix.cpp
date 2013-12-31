#include <vector>
#include <iostream>
using namespace std;

/*
Set matrix col/rows to zero
Given a matrix of 0s nd 1s. Write a function that check if an element is 
0 or not and places zeros to all the col and row of that element. eg:

input:
1 1 0 1
1 0 1 1
1 1 1 1
1 1 1 1

output:

0 0 0 0
0 0 0 0
1 0 0 1
1 0 0 1

The time complexity of the implementation below is O(M*N).



void set_col_row_zero(int A[M][N])
*/

int main() {
	vector<vector<int>> matrix = { { 1, 0, 1, 1 },
								   { 0, 1, 1, 1 },
								   { 1, 1, 1, 1 },
								   { 1, 1, 1, 1 } };

	vector<int> col_info(matrix.size(), 1);
	vector<int> row_info(matrix.size(), 1);

	for (int row = 0; row < matrix.size(); row++) {

		if (row_info[row] == 1) {
			for (int col = 0; col < matrix[row].size(); col++) {
				cout << matrix[row][col] << ' ';

				if (col_info[col] == 1) {
					if (matrix[row][col] == 0) {
						col_info[col] = 0;
						row_info[row] = 0;
					}
				}
			}
		}
		cout << endl;
	}

	for (int row = 0; row < matrix.size(); row++) {
		for (int col = 0; col < matrix[row].size(); col++) {
			if (col_info[col] == 0 || row_info[row] == 0) {
				matrix[row][col] = 0;
			}
		}
	}

	for (int row = 0; row < matrix.size(); row++) {
		for (int col = 0; col < matrix[row].size(); col++) {
			cout << matrix[row][col] << ' ';
		}
		cout << endl;
	}
}