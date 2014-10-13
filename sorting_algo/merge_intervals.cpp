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

class interval {
public:
  int start;
  int end;

  interval(int s, int e): start(s), end(e) {}
};

vector<interval> merge_intervals(vector<interval> &r) {
  vector<interval> out;
  stack<interval> s; 
  
  if(r.size() == 0) {
    return out;
  }
  else if(r.size() == 1) {
    out = r;
    return out;
  }

  std::sort(r.begin(), r.end(), [](const interval &r1, const interval &r2) { return r1.start < r2.start; });

  for (auto e : r) {
    if (s.empty()) {
      s.push(e);
    } else {
      auto top = s.top();

      // check for overlapping
      if(e.start <= top.end) {
        top.end = max(e.end, top.end);
        
        s.pop();
        s.push(top);
      } else {
        s.push(e);
      }
    }   
  }
  
  r.clear();
  
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
