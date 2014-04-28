/* 
Resource Acquisition is Initialization (RAII)
Use objects to manage resources: 
memory, hardware device, network handle, etc.
*/

Mutex_t   mu = MUTEX_INITIALIZER;
 
void functionA()
{
   Mutex_lock( &mu );
   ... // Do a bunch of things
   Mutex_unlock( &mu );      // Will this line always be executed?
}

// Solution: 
class Lock {
   privat:
      Mutext_t* m_pm;
   public:
      explicit Lock(Mutex_t *pm) { Mutex_lock(pm); m_pm = pm;};  
      ~Lock() { Mutex_unlock(m_pm); };
}

void functionA()
{
   Lock mylock(&mu);
   ...  // Do a bunch of things
}  // The mutex will always be released when mylock is destroied from stack