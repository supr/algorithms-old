#include <iostream>
#include <thread>
#include <condition_variable>
using namespace std;

/* Question:
Implement a semaphore
*/

class Semaphore {
private:
    int counter;
    int counter_max;
    std::condition_variable cv;
    std::mutex cv_m;
    
public:
    Semaphore(const int counter_): counter(counter_), counter_max(counter_) {}
    
    void wait() {
        std::unique_lock<std::mutex> lk(cv_m);
        cv.wait(lk, [this]{return counter > 0;});
        counter--;
    }
    
    void signal() {
        std::unique_lock<std::mutex> lk(cv_m);
        if(counter < counter_max) {
            counter++;
            cv.notify_one();
        }
    }    
};

class ThreadClass {
private:
    Semaphore s{1};

public:
    void print1(const string &str) {
        for(int i = 0; i < 10; i++) {
            s.wait();
            cout << str << i << endl;
            s.signal();
        }
    }
    
    void print2(const string &str) {
        for(int i = 0; i < 10; i++) {
            s.wait();
            cout << str << i << endl;
            s.signal();
        }
    }
};

int main()
{
    ThreadClass tc;
    thread t1(&ThreadClass::print1, &tc, "thread1: ");
    thread t2(&ThreadClass::print2, &tc, "thread2: ");
    
    t1.join();
    t2.join();
    
    return 0;
}
