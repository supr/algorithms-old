/* Question:
How would you implement a mutex?
*/

int guard = 0;
int value = FREE;

// atomic execution by hardware
bool test_and_set(bool &mutex) {
   bool tmp = mutex;
   mutex = true;
   return tmp;
}

Aquire() {
    // short busy-wait time
    while(test_and_set(guard));
    if(value == BUSY) {
        put thread on wait queue;
        go to sleep & guard = 0;
    }
    else {
        value = BUSY;
        guard = 0;
    }
}

Release() {
    // short busy-wait time
    while(test_and_set(guard));
    if anyone on wait queue {
        take thread off wait queue;
        place on ready queue;
    }
    else {
        value = FREE;
    }
    guard = 0;
}
