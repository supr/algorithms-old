#include <iostream>
#include <vector>
#include <deque>
using namespace std;

/*
Define a queue in which we can get its maximum number with a function max. In this 
stack, the time complexity of max, push_back, and pop_front are all O(1).
*/

typedef struct node {
	node *next;
	int value;
	node(int value_): value(value_), next(NULL) {}
}node;

class my_queue {
private:
	node *first;
	node *last;
	deque<int> curr_max;
	int count;
	
public:
	my_queue(): first(NULL), last(NULL), count(0) {}
	
	bool empty() {
		return count == 0;
	}
	
	void push_back(int value) {
		node *n = new node(value);
		
		if(!last) {
			last = n;
			first = n;
			curr_max.push_back(value);
		}
		else {
			last->next = n;
			last = n;
			
			for(int i = 0; i < curr_max.size(); i++) {
				if(value > curr_max[i]) {
					int elem_count = curr_max.size() - i;
					
					while(elem_count) {
						curr_max.pop_back();
						elem_count--;
					}
					
					break;
				}
			}
			
			curr_max.push_back(value);
		}
		
		count++;
	}
	
	void pop_front() {
		if(!first) {
			throw("queue is empty");
		}
		
		node *n = first;
		first = first->next;
		if(n->value == curr_max.front()) {
			curr_max.pop_front();
		}
		
		count--;
		delete n;
	}
	
	int max() {
		if(!first) {
			throw("queue is empty");
		}
		
		return curr_max.front();
	}
};

int main() {
	// your code goes here
	vector<int> vec = {1, 5, 6, 3, 5, 2, 4};
	my_queue q;
	
	for(int i = 0; i < vec.size(); i++) {
		q.push_back(vec[i]);
	}
	
	while(!q.empty()) {
		cout << q.max() << endl;
	    q.pop_front();
	}
	
	return 0;
}
