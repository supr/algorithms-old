#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/* Question:
Given a set of time intervals in any order, merge all overlapping intervals 
into one and output the result which should have only mutually exclusive intervals. 
Let the intervals be represented as pairs of integers for simplicity. 
*/

typedef struct interval {
	int start;
	int end;
	interval(int start_, int end_): start(start_), end(end_) {}
}interval;

typedef struct comparison {
	bool operator()(const interval &lhs, const interval &rhs) {
		return lhs.start < rhs.start;
	}
}comparison;

vector<interval> merge_intervals(vector<interval> &vec) {
	vector<interval> out;
	stack<interval> s;
	
	if(vec.size() == 0) {
		return out;
	}
	else if(vec.size() == 1) {
		out = vec;
		return out;
	}
	
	std::sort(vec.begin(), vec.end(), comparison());
	s.push(vec[0]);
	
	for(int i = 1; i < vec.size(); i++) {
		interval top = s.top();
		
		if(vec[i].start > top.end) {
			s.push(vec[i]);
		}
		else if(vec[i].start <= top.end) {
			s.pop();
			
			if(vec[i].end > top.end) {
				top.end = vec[i].end;
			}
			
			s.push(top);
		}
	}
	
	while(!s.empty()) {
		out.push_back(s.top());
		s.pop();
	}
	
	return out;
}

int main() {
	// your code goes here
	
	vector<interval> intervals1 = { {6,8}, {1,9}, {2,4}, {4,7} };
    vector<interval> intervals1_merged = merge_intervals(intervals1);
    for_each(intervals1_merged.begin(), intervals1_merged.end(), [](interval interv) { cout << interv.start << "," << interv.end << "; "; });
	
	cout << '\n';
	
	vector<interval> intervals2 = { {6,8},{1,3},{2,4},{4,7} };
    vector<interval> intervals2_merged = merge_intervals(intervals2);
    for_each(intervals2_merged.begin(), intervals2_merged.end(), [](interval interv) { cout << interv.start << "," << interv.end << "; "; });
    
    cout << '\n';
    
    vector<interval> intervals3 = { {1,3},{7,9},{4,6},{10,13} };
    vector<interval> intervals3_merged = merge_intervals(intervals3);
    for_each(intervals3_merged.begin(), intervals3_merged.end(), [](interval interv) { cout << interv.start << "," << interv.end << "; "; });
    
	return 0;
}
