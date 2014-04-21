#include <iostream>
#include <stack>
using namespace std;

/* Question:
How would you design a stack which, in addition to push and pop, also has a
function min which returns the minimum element? Push, pop and min should all
operate in 0(1) time.
*/

typedef struct value_min {
	int value;
	int min;
	value_min(int value_, int min_) : value(value_), min(min_) {}
}value_min;

class MyStack {
private:
	stack<value_min> s;

public:
	void push(int value) {
		int curr_min = value;

		if (!s.empty()) {
			if (s.top().min < value) {
				curr_min = s.top().min;
			}
		}

		s.push(value_min(value, curr_min));
	}

	int pop() {
		int value = s.top().value;
		s.pop();

		return value;
	}

	int min() {
		if (s.empty()) {
			return 0;
		}

		return s.top().min;
	}
};

int main() {
	// your code goes here

	MyStack s;
	s.push(5); // stack is {5}, min is 5
	cout << s.min() << endl;
	s.push(6); // stack is {6, 5}, min is 5
	cout << s.min() << endl;
	s.push(3); // stack is {3, 6, 5}, min is 3
	cout << s.min() << endl;
	s.push(7); // stack is {7, 3, 6, 5}, min is 3
	cout << s.min() << endl;
	s.pop(); // pops 7. stack is {3, 6, 5}, min is 3
	cout << s.min() << endl;
	s.pop(); // pops 3. stack is {6., 5}. min is 5.
	cout << s.min() << endl;

	return 0;
}
