#include <iostream>
#include <vector>
using namespace std;

// Runtime Polymorphism
// greek: "poly" – many, "morph" - form
// the same method can be called on different objects
// When you call a function with a common name, the runtime decides which implementation to call depending 
// on the current program context.
// The main thing to note about the below program is, derived class (Rectangle, Triangle) function is called 
// using a base class pointer (Polygon). The idea is, virtual functions are called according to the type of 
// object pointed or referred, not according to the type of pointer or reference. In other words, virtual 
// functions are resolved late, at runtime.
//
// How does compiler do this magic of late resolution?
// Compiler maintains two things to this magic:
// vtable: A table of function pointers. It is maintained per class.
// vptr: A pointer to vtable. It is maintained per object.
//
// Compiler adds additional code at two places to maintain and use vptr.
// 1) Code in every constructor. This code sets vptr of the object being created. This code sets vptr to 
// point to vtable of the class.
// 2) Code with polymorphic function call (e.g. bp->show() in above code). Wherever a polymorphic call is 
// made, compiler inserts code to first look for vptr using base class pointer or reference (In the above 
// example, since pointed or referred object is of derived type, vptr of derived class is accessed). Once 
// vptr is fetched, vtable of derived class can be accessed. Using vtable, address of derived derived class 
// function show() is accessed and called.
// if a class has any virtual function, it should have a virtual destructor, and that classes not designed 
// to be base classes or not designed to be used polymorphically should not declare virtual destructors.

class Polygon
{
protected:
  int width;
  int height;

public:
  Polygon(int width_, int height_): width(width_), height(height_) {}
  virtual ~Polygon(){}

  virtual int area() {
    return 0;
  }
}; 

class Rectangle : public Polygon
{
public:
  Rectangle(int width_, int height_): Polygon(width_, height_) {}

  int area() {
    return width * height;
  }
}; 

class Triangle : public Polygon
{
public:
  Triangle(int width_, int height_): Polygon(width_, height_) {}

  int area() {
    return width * height / 2;
  }
}; 

// Compile-Time Polymorphism
// Instead of inheriting behavior from a base class and overriding it, the Child, or implementing type, is passed 
// in as an instantiation argument. This creates a new type, which is the dynamic behavior we want. Using the 
// following code, we achieve the same output as before. 

template <class Operator> 
class Calculator 
{ 
public: 
    Calculator(){} 
    virtual ~Calculator(){}

    int calculate(int i1, int i2) { 
        return doOperation.operator()(i1, i2); // This is the "inner" function.
    } 
  
private: 
    Operator doOperation; 
}; 
  
class Adder /* Notice the lack of inheritance here */
{ 
public: 
    Adder() {} 
    virtual ~Adder(){}

    int operator() (int i1, int i2) { 
        return i1 + i2; 
    } 
}; 
  
class Multiplier 
{ 
public: 
    Multiplier() {} 
    virtual ~Multiplier(){}

    int operator() (int i1, int i2) { 
        return i1 * i2; 
    } 
};

int main () 
{
  vector<std::shared_ptr<Polygon>> polygons;
  polygons.push_back(std::shared_ptr<Polygon>(new Rectangle(2,2)));
  polygons.push_back(std::shared_ptr<Polygon>(new Triangle(2,2)));

  for_each(polygons.begin(), polygons.end(), [](std::shared_ptr<Polygon> sp) { cout << sp.get()->area() << endl; } );


  Calculator<Adder> *c1 = new Calculator<Adder>(); 
  cout << c1->calculate(2, 3) << endl;
  delete c1;

  Calculator<Multiplier> *c2 = new Calculator<Multiplier>(); 
  cout << c2->calculate(2, 3) << endl;
  delete c1;

  return 0;
}
