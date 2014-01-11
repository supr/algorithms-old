#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/* Question:
On a 2-D grid, the positions (x,y) of 3 persons are given. Find the meeting point such
that sum of distances of each person from meeting point is minimized. Now generalize
this to N persons and solve.
The people can not walk along diagonals.

Sulution:
- baed on Manhattan distance: Manhattan is |x-x1| + |y-y1|
- look for the median in x dim
- look for the median in y dim
- set meeting point to be median_x, median_y

If people would be able to walk along diagonals use Eucleadiean distance
-> http://en.wikipedia.org/wiki/Fermat_point

*/

enum pos_dim { dim_x = 0, dim_y = 1 };

typedef struct pos {
	int x;
	int y;
	pos(int x_, int y_) : x(x_), y(y_) {}
}pos;

typedef struct comparison_x {
	bool operator()(const pos lhs, const pos rhs) {
		return lhs.x < rhs.x;
	}
}comparison_x;

typedef struct comparison_y {
	bool operator()(const pos lhs, const pos rhs) {
		return lhs.y < rhs.y;
	}
}comparison_y;

int find_median(vector<pos> people, pos_dim dimension) {
	vector<pos>::iterator it_median = people.begin();

	if (dimension == dim_x) {
		nth_element(people.begin(), it_median + (people.size() / 2), people.end(), comparison_x());

		return people[people.size() / 2].x;
	}
	else if (dimension == dim_y) {
		nth_element(people.begin(), it_median + (people.size() / 2), people.end(), comparison_y());

		return people[people.size() / 2].y;
	}

	return -1;
}

pos find_meeting_point(vector<pos> &people) {
	int meeting_point_x = find_median(people, dim_x);
	int meeting_point_y = find_median(people, dim_y);

	return pos(meeting_point_x, meeting_point_y);
}

int main() {
	// your code goes here

	vector<pos> people1 = { { 0, 0 }, { 1, 3 }, { 4, 1 } };

	pos meeting_point1 = find_meeting_point(people1);

	cout << "Meeting point for people at set 1: " << endl;
	cout << meeting_point1.x << endl;
	cout << meeting_point1.y << endl;


	vector<pos> people2 = { { 1, 1 }, { 2, 3 }, { 3, 1 } };

	pos meeting_point2 = find_meeting_point(people2);

	cout << "Meeting point for people at set 2: " << endl;
	cout << meeting_point2.x << endl;
	cout << meeting_point2.y << endl;


	vector<pos> people3 = { { 0, 0 }, { 1, 1 }, { 2, 2 } };

	pos meeting_point3 = find_meeting_point(people3);

	cout << "Meeting point for people at set 3: " << endl;
	cout << meeting_point3.x << endl;
	cout << meeting_point3.y << endl;

	return 0;
}