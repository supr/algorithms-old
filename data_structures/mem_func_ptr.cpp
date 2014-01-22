#include <iostream>
#include <vector>
using namespace std;

class Test {
public:
	void mytest1(const char *info) {
		cout << "mytest1 " << info << endl;
	}

	void mytest2(const char *info) {
		cout << "mytest2 " << info << endl;
	}
};

typedef void (Test::*MemFuncPtr)(const char*);

class Foo {
private:
	vector<MemFuncPtr> vec;

public:
	void add(MemFuncPtr f) {
		vec.push_back(f);
	}

	void call_functions(Test *test) {
		for (auto it = vec.begin(); it != vec.end(); it++) {
			MemFuncPtr fPtr = *it;
			(test->*fPtr)("called");
		}
	}
};

int main() {
	Foo f;
	Test t;
	f.add(&Test::mytest1);
	f.add(&Test::mytest2);

	f.call_functions(&t);

	return 0;
}