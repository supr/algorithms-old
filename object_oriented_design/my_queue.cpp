#include <iostream>
#include <stack>
using namespace std;

/*
Implement a MyQueue class which implements a queue using two stacks
*/

class MyQueue {
private:
	stack<int> s1;
	stack<int> s2;

public:
	void push(int value) {
		while (!s2.empty()) {
			s1.push(s2.top());
			s2.pop();
		}

		s1.push(value);
	}

	void pop() {
		while (!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}

		if (!s2.empty()) {
			s2.pop();
		}
	}

	int front() {
		while (!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}

		return s2.top();
	}

	bool empty() {
		return (s1.empty() && s2.empty());
	}
};

int main() {
	// your code goes here

	MyQueue q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty()) {
		cout << q.front() << endl;

		q.pop();
	}

	return 0;
}