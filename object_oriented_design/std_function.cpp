#include <iostream>
#include <functional>

using namespace std;
using namespace placeholders;

/*
With c++11 we have a new way to deal with function and member function pointers under the functional header, the std::function wrapper.
*/

class Math {
public:
	void sum(int x, int y) {
		cout << "sum: " << x + y << endl;
	}

};

int main() {
	Math m;

	std::function<void(int, int)> func = std::bind(&Math::sum, &m, _1, _2);
	func(10, 20);

	return 0;
}