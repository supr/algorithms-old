#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

/*
Adapter Pattern
The adapter pattern (often referred to as the wrapper pattern or simply a wrapper) is a design pattern
that translates one interface for a class into a compatible interface. An adapter allows classes to work
together that normally could not because of incompatible interfaces, by providing its interface to
clients while using the original interface.
*/

enum Color {
	red,
	green,
	blue
};

class Shape
{
public:
	virtual void display() {}
};

class AlreadyImplementedCircle {
public:
	void display() { cout << "AlreadyImplementedCircle showCircle" << endl; }
	void changeColor(Color color) {}
	void scale(float factor1, float factor2) {}
};

class Circle : public Shape
{
private:
	AlreadyImplementedCircle *c;

public:
	Circle() { c = new AlreadyImplementedCircle(); }
	void display() { c->display(); }
	void setColor(Color color) { c->changeColor(color); }
	void scale(float factor) { c->scale(factor, factor); }

	~Circle() { delete c; }
};

class AlreadyImplementedRectangle {
public:
	void display() { cout << "AlreadyImplementedRectangle showRectangle" << endl; }
	void changeColor(Color color) {}
	void scale(float factor1, float factor2) {}
};

class Rectangle : public Shape
{
private:
	AlreadyImplementedRectangle *c;

public:
	Rectangle() { c = new AlreadyImplementedRectangle(); }
	void display() { c->display(); }
	void setColor(Color color) { c->changeColor(color); }
	void scale(float factor) { c->scale(factor, factor); }

	~Rectangle() { delete c; }
};

class AlreadyImplementedLine {
public:
	void display() { cout << "AlreadyImplementedLine showLine" << endl; }
	void changeColor(Color color) {}
	void scale(float factor1, float factor2) {}
};

class Line : public Shape
{
private:
	AlreadyImplementedLine *c;

public:
	Line() { c = new AlreadyImplementedLine(); }
	void display() { c->display(); }
	void setColor(Color color) { c->changeColor(color); }
	void scale(float factor) { c->scale(factor, factor); }

	~Line() { delete c; }
};

int main()
{
	list<Shape*> shapes;

	Shape *rect = new Rectangle();
	Shape *line = new Line();
	Shape *circle = new Circle();

	shapes.push_back(rect);
	shapes.push_back(line);
	shapes.push_back(circle);

	// display all gemoetric figures 
	for (auto iter = shapes.begin(); iter != shapes.end(); iter++) {
		(*iter)->display();
	}

	// delete allocated objects

	return 0;
}