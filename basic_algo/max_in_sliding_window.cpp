#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
using namespace std;

/*
Given an array of numbers and a sliding window size, how do you get the maximum numbers in all sliding windows?
For example, if the input array is {2, 3, 4, 2, 6, 2, 5, 1} and the size of the sliding windows is 3, 
the output of maximums are {4, 4, 6, 6, 6, 5}

Sliding Windows in an Array		Maximums in Sliding Windows
[2,3,4],2,6,2,5,1                       4 
2,[3,4,2],6,2,5,1                       4
2,3,[4,2,6],2,5,1                       6
2,3,4,[2,6,2],5,1                       6
2,3,4,2,[6,2,5],1                       6
2,3,4,2,6,[2,5,1]                       5
*/

// time complexity: O(n * k)
vector<int> maxInWindow(vector<int> maxi, unsigned int windowSize) {
  for(auto it = maxi.begin(); it != maxi.end(); it++) {
    *it = *max_element(it, it + windowSize);

    if(it + windowSize == maxi.end()) {
      break;
    }
  }
	
  maxi.resize(maxi.size() - windowSize + 1);
  return maxi;
}

class node {
public:
  int index;
  int value;

  node(int index_, int value_): index(index_), value(value_) {}
};

struct Comparator {
  bool operator()(const node &lhs, const node &rhs) {
    return lhs.value < rhs.value;
  }
};

typedef priority_queue<node, vector<node>, Comparator> pq;

void removeIndex(pq &maxHeap, int index) {
  stack<node> copy;
  
  while (!maxHeap.empty()) {
    node n = maxHeap.top();
    maxHeap.pop();
    
    if (n.index == index) {
      break;
    }
    else {
      copy.push(n);
    }
  }

  while (!copy.empty()) {
     maxHeap.push(copy.top());  
     copy.pop();
  }
  
}

vector<int> maxInWindow2(vector<int> &vec, int k) {
  vector<int> out;
  pq maxHeap;

  for (int i = 0; i < vec.size(); i++) {
    if (i < k) {
      maxHeap.push(node(i, vec[i]));
      
      if (i == (k - 1)) {
        out.push_back(maxHeap.top().value);
      }
    }
    else {
      maxHeap.push(node(i, vec[i]));
      removeIndex(maxHeap, i - k);
      out.push_back(maxHeap.top().value);
    }     
  }

  return out;
}

int main() {
	// your code goes here
	
	vector<int> numbers = {2, 3, 4, 2, 6, 2, 5, 1};
	vector<int> maxi = maxInWindow(numbers, 3);
	
	for(auto value : maxi) {
		cout << value << endl;
	}

  vector<int> vec = {1,2,5,7,3,1,7,9,0};
  vector<int> out = maxInWindow2(vec, 2);
    
  for (auto e : out) {
    cout << e << ' ';
  }

	return 0;
}
