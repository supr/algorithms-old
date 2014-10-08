#include <iostream> 
#include <thread> 
#include <mutex> 
#include <condition_variable> 
#include <vector> 
#include <algorithm> 
#include <cassert> 
using namespace std; 

/* Question:
Your system uses 3 threads and 2 shared resources:
Thread1 can access resource 1
Thread2 can access resource 1 and resource 2
Thread3 can access resource 1 and resource 2

Which synchronization would you use?
*/
  
class SynchronizationTest { 
private: 
    mutex lock_r1; 
    mutex lock_r2; 
    vector<pair<string, int>> buffer_r1; 
    vector<pair<string, int>> buffer_r2; 
    unsigned int buffer_r1_max_size; 
    unsigned int buffer_r2_max_size; 
  
    bool buffer_r1_inc_element(const string &thread_id) {       
        if (buffer_r1.size() == buffer_r1_max_size) { 
            return true;
        } 
  
        if (buffer_r1.size() == 0) { 
            buffer_r1.push_back(make_pair(thread_id, 0)); 
        } 
        else { 
            int last_val = buffer_r1.back().second; 
            buffer_r1.push_back(make_pair(thread_id, ++last_val)); 
        } 
        
        return false;
    } 
  
    bool buffer_r2_inc_element(const string &thread_id) {  
        if (buffer_r2.size() == buffer_r2_max_size) { 
            return true;
        } 
  
        if (buffer_r2.size() == 0) { 
            buffer_r2.push_back(make_pair(thread_id, 0)); 
        } 
        else { 
            int last_val = buffer_r2.back().second; 
            buffer_r2.push_back(make_pair(thread_id, ++last_val)); 
        } 
        
        return false;
    } 
  
public: 
    SynchronizationTest(int buff_r1_size, int buff_r2_size) : buffer_r1_max_size(buff_r1_size), 
                                                              buffer_r2_max_size(buff_r2_size) {} 
  
    void thread1() { 
        bool buffer_r1_full = false; 
  
        while (!buffer_r1_full) { 
            { 
                unique_lock<mutex> l(lock_r1, std::defer_lock); 
                if (l.try_lock()) { 
                    buffer_r1_full = buffer_r1_inc_element("thread1"); 
                } 
            } 
            
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
        } 
    } 
  
    void thread2() { 
        bool buffer_r1_full = false; 
        bool buffer_r2_full = false; 
  
        while (!buffer_r1_full || !buffer_r2_full) {
            {
                unique_lock<mutex> lock1(lock_r1, defer_lock);
                unique_lock<mutex> lock2(lock_r2, defer_lock);

                bool result1 = lock1.try_lock();
                bool result2 = lock2.try_lock();
                
                if(result1 && result2) {
                    buffer_r1_full = buffer_r1_inc_element("thread2");
                    buffer_r2_full = buffer_r2_inc_element("thread2");
                }
                else if(result1) { 
                    buffer_r1_full = buffer_r1_inc_element("thread2");
                }
                else if(result2) { 
                    buffer_r2_full = buffer_r2_inc_element("thread2");
                }
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
        } 
    } 
  
    void thread3() { 
        bool buffer_r1_full = false; 
        bool buffer_r2_full = false; 
  
        while (!buffer_r1_full || !buffer_r2_full) { 
            {
                unique_lock<mutex> lock1(lock_r1, defer_lock);
                unique_lock<mutex> lock2(lock_r2, defer_lock);

                bool result1 = lock1.try_lock();
                bool result2 = lock2.try_lock();
                if(result1 && result2) {
                    buffer_r1_full = buffer_r1_inc_element("thread3");
                    buffer_r2_full = buffer_r2_inc_element("thread3");
                }
                else if(result1) { 
                    buffer_r1_full = buffer_r1_inc_element("thread3");
                }
                else if(result2) { 
                    buffer_r2_full = buffer_r2_inc_element("thread3");
                }
            }
  
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
        } 
    } 
  
    void print_buffer() { 
        for_each(buffer_r1.begin(), buffer_r1.end(), [](pair<string, int> p) { cout << p.first.c_str() << " " << p.second << endl; }); 
        cout << '\n'; 
        for_each(buffer_r2.begin(), buffer_r2.end(), [](pair<string, int> p) { cout << p.first.c_str() << " " << p.second << endl; }); 
    } 
}; 
  
int main() { 
    // your code goes here 
    SynchronizationTest st(20, 20); 
  
    thread t1(&SynchronizationTest::thread1, &st); 
    thread t2(&SynchronizationTest::thread2, &st); 
    thread t3(&SynchronizationTest::thread3, &st); 
  
    t1.join(); 
    t2.join(); 
    t3.join(); 
    
    st.print_buffer(); 
  
    return 0; 
}
