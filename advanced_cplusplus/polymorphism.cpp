#include <iostream>
#include <vector>
using namespace std;

// Runtime Polymorphism
class Polygon
{
protected:
  int width;
  int height;

public:
  Polygon(int width_, int height_): width(width_), height(height_) {}
    
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


int main ()
{
  vector<std::shared_ptr<Polygon>> polygons;
  polygons.push_back(std::shared_ptr<Polygon>(new Rectangle(2,2)));
  polygons.push_back(std::shared_ptr<Polygon>(new Triangle(2,2)));

  for_each(polygons.begin(), polygons.end(), [](std::shared_ptr<Polygon> sp) { cout << sp.get()->area() << endl; } );

  return 0;
}