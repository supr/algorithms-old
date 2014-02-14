#include <iostream>
#include <vector>
using namespace std;

typedef enum direction {
	go_left = 0,
	go_down = 1,
	go_right = 2,
	go_up = 3
}direction;

typedef struct row_col_info {
	int row_min;
	int row_max;
	int col_min;
	int col_max;

	row_col_info(int row_min_, int row_max_, int col_min_, int col_max_) : 
		row_min(row_min_),
		row_max(row_max_),
		col_min(col_min_),
		col_max(col_max_) {}
}row_col_info;

vector<vector<int>> create_matrix_inc_number(int N) {
	vector<vector<int>> matrix(N);
	int number = 0;
	int row = 0;
	int col = 0;
	direction dir = go_right;
	row_col_info info(1, N-1, 0, N-1);

	for (int i = 0; i < N; i++) {
		matrix[i].resize(N);
	}

	while (number < N*N) {
		matrix[row][col] = number;
		number++;

		switch (dir) {
		case go_right:
			col++;

			if (col == info.col_max) {
				dir = go_down;
				info.col_max = info.col_max - 1;
			}
			break;
		case go_down:
			row++;

			if (row == info.row_max) {
				dir = go_left;
				info.row_max = info.row_max - 1;
			}
			break;
		case go_left:
			col--;

			if (col == info.col_min) {
				dir = go_up;
				info.col_min = info.col_min + 1;
			}
			break;
		case go_up:
			row--;

			if (row == info.row_min) {
				dir = go_right;
				info.row_min = info.row_min + 1;
			}
			break;
		default:
			break;
		}
	}

	return matrix;
}

int main() {
	// your code goes here

	const int N = 4;
	vector<vector<int>> m = create_matrix_inc_number(N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << m[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
