#include <iostream>
#include <functional>

using namespace std;
using namespace placeholders;

/*
With c++11 we have a new way to deal with function and member function pointers under the functional
header, the std::function wrapper.

- std::function is a STL template class that provides a very convenient wrapper to a simple function, 
to a functor or to a lambda expression.
- An std::function overloads the operator() making it a functor object.
- An std::function is a wrapper that can hold any type of callable object (objects that look like functions).
*/

class Math {
public:
	void sum1(int x, int y) {
		cout << "sum1: " << x + y << endl;
	}

  	static void diff(int x, int y) {
    		cout << "diff: " << x - y << endl;
  	}
};

static void sum2(int x, int y) {
	cout << "sum2: " << x + y << endl;
}

int main() {
	Math m;

	std::function<void(int, int)> func1 = std::bind(&Math::sum1, &m, _1, _2);
	func1(10, 20);

  	std::function<void(int, int)> func2 = std::bind(&sum2, _1, _2);
  	func2(10, 20);

  	std::function<void(int, int)> func3 = std::bind(&Math::diff, _1, _2);
  	func3(10, 20);

	return 0;
}
