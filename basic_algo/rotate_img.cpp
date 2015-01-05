#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

/*
Question: Rotate Image
You are given an n x n 2D matrix representing an image.
Rotate the image by 90 degrees (clockwise).
Follow up:
Could you do this in-place?
*/

void rotate_image(vector<vector<int>> &img) {
  int n = img.size() - 1;
  int offset = 0;

  for (int layer = 0; layer < img.size() / 2; layer++) {
    int first = layer;
    int last = n - layer;

    for (int i = first; i < last; i++) {
      // save 1st row
      int top = img[first][last-i];
      // replace 1st row with first colum
      img[first][last-i] = img[i][first];
      // replace first colum with last row
      img[i][first] = img[last][i];
      // replace last row with last colum
      img[last][i] = img[last-i+offset][last];
      // replace last colum with 1st row
      img[last-i+offset][last] = top;
    }

    offset += 1;
  }
}

int main() {
  vector<vector<int>> vec = { { 1, 1, 1, 1 },
  { 2, 2, 2, 2 },
  { 3, 3, 3, 3 },
  { 4, 4, 4, 4 } };

  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].size(); j++) {
      cout << vec[i][j] << ' ';
    }
    cout << '\n';
  }

  cout << '\n';

  rotate_image(vec);

  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].size(); j++) {
      cout << vec[i][j] << ' ';
    }
    cout << '\n';
  }

  return 0;
}