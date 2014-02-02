#include <iostream> 
#include <queue>
#include <thread> 
#include <mutex> 
#include <condition_variable> 
using namespace std;

/* Question: 
Implemented the Producer Consumer Problem

The  Producer Consumer problem is a classic example of a multi-process synchronization problem. The problem describes two processes, the 
producer and the consumer, who share a common, fixed-size buffer used as a queue. The producer's job is to generate a piece of data, 
put it into the buffer and start again. At the same time, the consumer is consuming the data (i.e., removing it from the buffer) one 
piece at a time. The problem is to make sure that the producer won't try to add data into the buffer if it's full and that the consumer 
won't try to remove data from an empty buffer.
*/

class ProducerConsumer {
private:
	queue<int> q;
	int count;
	int capacity;
	mutex lock;
	mutex m;
	condition_variable not_full;
	condition_variable not_empty;

public:
	ProducerConsumer(int capacity_) : count(0), capacity(capacity_) {}

	void deposit(int value) {
		unique_lock<mutex> l(lock);
		not_full.wait(l, [this](){ return count != capacity; });
		
		q.push(value);
		++count;

		not_empty.notify_one();
	}

	int fetch() {
		unique_lock<mutex> l(lock);
		not_empty.wait(l, [this](){ return count != 0; });
		
		int value = q.front();
		q.pop();
		--count;

		not_full.notify_one();

		return value;
	}

	void producer(int id) {
		for (int i = 0; i < 30; ++i){
			deposit(i);

			{
				unique_lock<mutex> l(m);
				cout << "Produced " << id << " produced " << i << endl;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	void consumer(int id) {
		for (int i = 0; i < 10; ++i){
			int value = fetch();

			{
				unique_lock<mutex> l(m);
				cout << "Consumer " << id << " fetched " << value << std::endl;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
	}
};

int main() {
	// your code goes here 

	ProducerConsumer p(1);
	thread c1(&ProducerConsumer::consumer, &p, 1);
	thread c2(&ProducerConsumer::consumer, &p, 2);
	thread c3(&ProducerConsumer::consumer, &p, 3);
	thread p1(&ProducerConsumer::producer, &p, 1);

	c1.join();
	c2.join();
	c3.join();
	p1.join();

	cout << "\nThreads successfully completed..." << endl;

	return 0;
}