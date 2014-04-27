// compile and run: g++ -std=c++11 -I/usr/local/Cellar/boost/1.55.0_1/include lfu_cache.cpp -o lfu_cache; ./lfu_cache
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <boost/heap/d_ary_heap.hpp>
using namespace std;

typedef struct entry {
	int key;
	int value;
	int local_counter;
 	int global_counter_start;
	entry(int key_, int value_, int global_counter_start_): key(key_), 
	                                                        value(value_),  
	                                                        local_counter(1), 
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
			float freq_rhs = static_cast<float>(rhs.local_counter) / (LFU_Cache::global_counter - rhs.global_counter_start);

			return freq_lhs < freq_rhs;  
    }
  };

  typedef typename boost::heap::d_ary_heap<entry, boost::heap::arity<2>, boost::heap::mutable_<true>, boost::heap::compare<Comparison>>::handle_type handle_t;  
  typedef boost::heap::d_ary_heap<entry, boost::heap::arity<2>, boost::heap::mutable_<true>, boost::heap::compare<Comparison>> MyPriQue; 
  MyPriQue pq;
  unordered_map<int, handle_t> ht;
  int cache_size;
   
private:
  void erase() {
  	auto key = pq.top().key;
  
    cout << "delete key: " << key << endl;
  
  	ht.erase(key);
    pq.pop();
  }
  
public:
  LFU_Cache(int cache_size_): cache_size(cache_size_) {}
  
	void insert(int key, int value) {
    int current_size = ht.size() + 1;
    if (current_size > cache_size) {
      erase();
    }
  
    cout << "insert key: " << key << endl;
      
    auto it = ht.find(key);

    if (it != ht.end()) {
      handle_t h = it->second;
      (*h).local_counter++;
      (*h).value = value;
      pq.update(h);
    }
    else {
      handle_t h = pq.push(entry(key, value, LFU_Cache::global_counter));
    
      ht.insert(make_pair(key, h));
    }
  
    LFU_Cache::global_counter++;
	}
  
	int find(int key) {
    auto it = ht.find(key);
 
  	if (it != ht.end()) {
      handle_t h = it->second;
      (*h).local_counter++;
      LFU_Cache::global_counter++;
      pq.update(h);
    
  		return (*h).value;
  	}
 
  	return 0;
	}
  
  void print() {
    for(auto it = pq.begin(); it != pq.end(); it++) {
      float freq = static_cast<float>(it->local_counter) / (LFU_Cache::global_counter - it->global_counter_start);
      cout << "\tkey: " << it->key << " \tfreq: " << freq << endl;
    }
    cout << "\tmin_key: " << pq.top().key << endl;
  }
};

unsigned int LFU_Cache::global_counter = 1;

int main() {
    LFU_Cache c(3);
    
    c.insert(1, 2);
    c.print();
    c.insert(3, 3);
    c.print();
    c.insert(3, 4);
    c.print();
    c.insert(1, 5);
    c.print();
    c.insert(4, 2);
    c.print();
    c.insert(5, 1);
    c.print();
    c.insert(6, 2);
    c.print();
    c.insert(6, 2);
    c.print();
    c.insert(4, 8);
    c.print();
    
    cout << c.find(3) << endl;
    //c.print();
    cout << c.find(1) << endl;
    cout << c.find(4) << endl;
    cout << c.find(5) << endl;
    cout << c.find(6) << endl;
    
    return 0;
}
