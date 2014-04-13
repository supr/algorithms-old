#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <memory>
using namespace std;

/* Question:
Design a resource pool, which promises FIFO to every client
*/

const int max_threads = 200;

class foo {
private:
	unsigned int resource_id;

public:
	foo(unsigned int resource_id_) : resource_id(resource_id_) {}

	unsigned int get_resource_id() {
		return resource_id;
		}
};

template <typename T>
class ResourcePool {
private:
	vector<T*> resources;
	vector<bool> aquired;
	mutex lock;
	int size;

public:
	ResourcePool(int size_) : size(size_) {
		for (int i = 0; i < size; i++) {
			T *instance = new T(i);
			resources.push_back(instance);
			aquired.push_back(false);
		}
}

~ResourcePool() {
	for (int i = 0; i < size; i++) {
		delete resources[i];
	}
}

T *get_resource() {
	unique_lock<mutex> l(lock);

	int i = 0;
	for (i = 0; i < resources.size(); i++) {
		if (aquired[i] == false) {
			aquired[i] = true;
			return resources[i];
		}
	}

	return NULL;
}

bool release_resource(T *resource) {
	if (resource == NULL) {
		return false;
	}

	unique_lock<mutex> l(lock);

	for (int i = 0; i < resources.size(); i++) {
		if (resources[i] == resource) {
			if (aquired[i] == false) {
				return false;
			}

			aquired[i] = false;
			return true;
		}
	}

	return false;
}
};

class worker_thread {
private:
	foo *resource;
	ResourcePool<foo> *p;

private:
	bool release() {
		if (resource) {
			return p->release_resource(resource);
		}

	return false;
	}

public:
	worker_thread() : resource(NULL), p(NULL) {}

	void create(mutex *lock, ResourcePool<foo> *ptr, unsigned int thread_id) {
		p = ptr;

		resource = p->get_resource();

		if (resource) {
			unique_lock<mutex> l(*lock);
			cout << "thread: " << thread_id << " got resource_id: " << resource->get_resource_id() << endl;
		}

		release();
	}
};

int main() {
	// your code goes here

	srand(time(NULL));

	ResourcePool<foo> p(10);
	vector<thread> workers;
	mutex lock;

	for (int thread_id = 0; thread_id < max_threads; thread_id++) {
		shared_ptr<worker_thread> w(new worker_thread);
		workers.push_back(std::thread(&worker_thread::create, w, &lock, &p, thread_id));
	}

	for (std::thread &t : workers) {
		if (t.joinable()) {
			t.join();
		}
	}

	return 0;
}
