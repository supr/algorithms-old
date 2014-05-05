#include <iostream>
#include <map>
#include <ctime>
#include <chrono>
#include <thread>
#include <functional>
using namespace std;
using namespace std::placeholders;

/* Question:
Design the data structure and algorithms to implement a timer with the following operations:
- callback() - Checking at some granularity for the next event(s) and call them.
- add
- remove
- change

Assume the clock interrupt happens a hundred times a second. The first three operations occur less frequently than the
last.

Assume a CPU with interrupts arriving 100 times per second and that the add/remove/change operations could be
assumed to be less frequent. Assume 1,000 - 2,000 timers are present at any given moment.

system_time = 5000
cpu_clock = 100hz
*/

class Test;

typedef void(*func)(unsigned int);

class Timer {
private:
	map<int, func> events;
	std::chrono::time_point<std::chrono::system_clock> start;

public:
	Timer() {
		// current time
		start = std::chrono::system_clock::now();
	}

	void add_event(int t, func f) {
		events.insert(make_pair(t, f));
	}

	void remove_event(func f) {
		for (auto it = events.begin(); it != events.end(); it++) {
			if (it->second == f) {
				events.erase(it);
				break;
			}
		}
	}

	void change_event(int t_new, func f) {
		bool found = false;

		for (auto it = events.begin(); it != events.end(); it++) {
			if (it->second == f) {
				events.erase(it);
				found = true;
				break;
			}
		}

		if (found) {
			events.insert(make_pair(t_new, f));
		}
	}

	void callback() {
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		unsigned int diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

		for (auto it = events.begin(); it != events.end(); it++) {
			if (diff > it->first) {
				it->second(diff);
				events.erase(it);
				break;
			}
		}
	}
};

void test1(unsigned int t) {
	cout << "test1 called, time: " << t << endl;
}

void test2(unsigned int t) {
	cout << "test2 called, time: " << t << endl;
}

void test3(unsigned int t) {
	cout << "test3 called, time: " << t << endl;
}

void test4(unsigned int t) {
	cout << "test4 called, time: " << t << endl;
}

class Test {
public:
	static void test5(unsigned int t) {
		cout << "test5 called, time: " << t << endl;
	}
};

void timer_irq(Timer &t) {
	while (true) {
		t.callback();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int main() {
	// your code goes here

	Timer t;
	t.add_event(6000, &test3);
	t.add_event(1000, &test1);
	t.add_event(5000, &test2);
	t.change_event(3000, &test1);
	t.remove_event(&test3);
	t.add_event(5500, &test4);
	t.add_event(2000, &Test::test5);

	std::thread cpu_clock_thread(timer_irq, std::ref(t));
	cpu_clock_thread.join();

	return 0;
}