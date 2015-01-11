#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <ctime>
using namespace std;

/* Question:
Given set of n points (Xi, Yi), write a function to find k nearest points from a given point x,y.

Solution:
based on sorting:       O(n log n) ... n = number of elements in vector
based on heap:          O(n long k) ... k = k clostest points, n = number of elements in vector
based on quick_select:  O(k * n^2)
*/

typedef struct coord {
  int x;
  int y;
  coord(int x_, int y_) : x(x_), y(y_) {}
}coord;

typedef struct dist_index {
  float dist;
  int index;
  dist_index(float dist_, int index_) : dist(dist_), index(index_) {}
}dist_index;

typedef struct comperison {
  bool operator()(const dist_index &lhs, const dist_index &rhs) {
    return lhs.dist < rhs.dist;
  }
}comparison;

vector<coord> find_k_nearest_points1(vector<coord> vec, coord p, int k) {
  if (vec.size() < k) {
    return vec;
  }

  vector<dist_index> dist;
  vector<coord> k_nearest_points;

  for (int i = 0; i < vec.size(); i++) {
    int x = abs(vec[i].x - p.x); 
    int y = abs(vec[i].y - p.y); 
    float distance = sqrt(x * x + y * y);

    dist.push_back(dist_index(distance, i));
  }

  sort(dist.begin(), dist.end(), comperison());

  for (int i = 0; i < k; i++) {
    k_nearest_points.push_back(vec[dist[i].index]);
  }

  return k_nearest_points;
}

vector<coord> find_k_nearest_points2(vector<coord> vec, coord p, int k) {
  if (vec.size() < k) {
    return vec;
  }

  priority_queue<dist_index, vector<dist_index>, comparison> max_heap;
  vector<coord> k_nearest_points;

  for (int i = 0; i < vec.size(); i++) {
    int x = abs(vec[i].x - p.x); 
    int y = abs(vec[i].y - p.y); 
    float distance = sqrt(x * x + y * y);

    if (max_heap.size() < k) {
      max_heap.push(dist_index(distance, i));
    }
    else {
      if (max_heap.top().dist > distance) {
        max_heap.pop();
        max_heap.push(dist_index(distance, i));
      }
    }
  }

  while (!max_heap.empty()) {
    int index = max_heap.top().index;
    max_heap.pop();

    k_nearest_points.push_back(vec[index]);
  }

  return k_nearest_points;
}

// this function partitions the array into:
// - left half which elements are smaller than the pivot
// - right half which elements are larger than the pivot
int rand_partition(vector<dist_index> &vec, int low, int high) {
  int l = low;
  int r = high;
  int pivot_index = l + rand() % (r - l); // (low + high) / 2; 
  int pivot = vec[pivot_index].dist;

  while (true) {
    while (vec[l].dist < pivot) l++;
    while (vec[r].dist > pivot) r--;
    if (l > r) break;
    std::swap(vec[l++], vec[r--]);
  }

  return l;
}

// we find the k largest distance
dist_index rand_select(vector<dist_index> &vec, int l, int r, int k) {
  if (l == r) {
    return vec[l];
  }

  int pivot_index = rand_partition(vec, l, r);

  if (pivot_index == k) {
    return vec[k];
  }
  else if (pivot_index > k) {
    return rand_select(vec, l, pivot_index - 1, k);
  }
  else if (pivot_index < k) {
    return rand_select(vec, pivot_index + 1, r, k);
  }
}

vector<coord> find_k_nearest_points3(vector<coord> vec, coord p, int k) {
  if (vec.size() < k) {
    return vec;
  }

  // calc all distances to p and stores all coordicates with distance, index to vec
  vector<dist_index> dist;
  // stores the k nearest points to p
  vector<coord> k_nearest_points;

  // calculate the distance between p and any point:
  // This calcuates the distance between two points: p and vec[i]
  // In 2D Define your two points. Point 1 at (x1, y1) and Point 2 at (x2, y2).
  // xd = x2-x1
  // yd = y2-y1
  // Distance = SquareRoot(xd*xd + yd*yd)
  for (int i = 0; i < vec.size(); i++) {
    int x = abs(vec[i].x - p.x); 
    int y = abs(vec[i].y - p.y); 
    float distance = sqrt(x * x + y * y);

    dist.push_back(dist_index(distance, i));
  }

  // we look for the smallest distance
  // if the smallest distance is found we replace it with <int>::max()
  // and search for the next smallest distance
  for (int i = 0; i < k; i++) {
    dist_index smallerst_dist = rand_select(dist, 0, dist.size() - 1, 0);

    //cout << smallerst_dist.dist << endl;

    int index = smallerst_dist.index;
    smallerst_dist.dist = numeric_limits<int>::max();

    k_nearest_points.push_back(vec[index]);
  }

  return k_nearest_points;
}

int main() {
  // your code goes here

  srand(time(0));

  vector<coord> vec = { { 1, 1 }, { 10, 2 }, { 8, 1 }, { 2, 2 }, { 5, 5 }, { 6, 2 }, { 3, 3 } };

  cout << "find_k_nearest_points1..." << endl;
  vector<coord> points = find_k_nearest_points1(vec, coord(2, 3), 2);
  for_each(points.begin(), points.end(), [](coord p) { cout << "x: " << p.x << ", y: " << p.y << endl; });

  cout << "find_k_nearest_points2..." << endl;
  vector<coord> points2 = find_k_nearest_points2(vec, coord(2, 3), 2);
  for_each(points2.begin(), points2.end(), [](coord p) { cout << "x: " << p.x << ", y: " << p.y << endl; });

  cout << "find_k_nearest_points3..." << endl;
  vector<coord> points3 = find_k_nearest_points3(vec, coord(2, 3), 2);
  for_each(points3.begin(), points3.end(), [](coord p) { cout << "x: " << p.x << ", y: " << p.y << endl; });

  return 0;
}