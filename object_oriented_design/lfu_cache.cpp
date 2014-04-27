#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <boost/heap/priority_queue.hpp>
#include <boost/heap/fibonacci_heap.hpp>
using namespace std;

typedef struct entry {
  int key;
  int value;
  int local_counter;
  int global_counter_start;
  entry(int key_, int value_, int global_counter_start_): key(key_), 
	                                                        value(value_),  
	                                                        local_counter(0), 
	                                                        global_counter_start(global_counter_start_) {}
}entry;

class LFU_Cache {
public:
  static unsigned int global_counter;

private:
  class Comparison {
  public:
    bool operator()(const entry &lhs, const entry &rhs) const {
      float freq_lhs = static_cast<float>(lhs.local_counter) / (LFU_Cache::global_counter - lhs.global_counter_start);
      float freq_rhs = static_cast<float>(lhs.local_counter) / (LFU_Cache::global_counter - rhs.global_counter_start);

      return freq_lhs < freq_rhs;  
    }
  };

  typedef boost::heap::fibonacci_heap<entry, boost::heap::compare<Comparison>> MyPriQue;
  MyPriQue pq;
  unordered_map<int, decltype(pq.begin())> ht;
  int cache_size;
   
private:
  void erase();
  
public:
  LFU_Cache(int cache_size_);
  void insert(int key, int value);
  int find(int key);
  void print();
};
