#include <iostream>
using namespace std;

class Foo { 
public:  
  Foo(int x) { cout << "Foo constructor" << endl; }
  Foo(const Foo &a) { cout << "Foo copy constructor" << endl; }
}; 
  
class Bar { 
public: 
  Bar(int x) { cout << "Bar constructor" << endl; }
}; 
  
class FooBar { 
public: 
  explicit FooBar(int x) { cout << "Bar constructor" << endl; }
}; 

int main() { 
    Foo f1(2); 
    Foo f2 = f1;
    Foo f3 = 2;
    
    Bar b = 2; // implicit convertion
    
    FooBar c = 3;
    
    return 0; 
}