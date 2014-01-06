#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

/* 
Abstract Factory Pattern
A Abstract Fatory defines an interface to generate products of concrete factorys. The abstract 
product also defines an interface to create concrete products. The abstract factory is useful for 
replaceability of concrete factorys without changing the clients code, because the client uses 
the abstract factory.
A Abstract Factory Pattern is a design pattern that provides a way to encapsulate a group of 
individual factories that have a common theme. In normal usage, the client software creates a 
concrete implementation of the abstract factory and then uses the generic interfaces to create 
the concrete objects that are part of the theme. The client does not know (or care) which concrete 
objects it gets from each of these internal factories since it uses only the generic interfaces 
of their products. This pattern separates the details of implementation of a set of objects from 
their general usage.
*/

// This is the AbstractProduct 
class Car
{
public:
	virtual void DisplayModel() = 0;
};

// This is a ConcreteProduct 
class Maruthi : public Car
{
public:
	virtual void DisplayModel()
	{
		cout << "Maruthi" << endl;
	}
};

// This is another ConcreteProduct 
class Ferrari : public Car
{
public:
	virtual void DisplayModel()
	{
		cout << "Ferrari" << endl;
	}
};

// This is the AbstractCreator 
class CarFactory
{
public:
	// This is the abstract declaration of the Factory Method. 
	virtual Car* CreateCar() = 0;
};

// This is a ConcreteCreator 
class MaruthiFactory : public CarFactory
{
public:
	MaruthiFactory() {}
	virtual ~MaruthiFactory() {}

	// This is a Concrete definition of the Factory Method 
	virtual Car* CreateCar()
	{
		return new Maruthi();
	}
};

// This is a ConcreteCreator 
class FerrariFactory : public CarFactory
{
public:
	FerrariFactory() {}
	virtual ~FerrariFactory() {}

	// This is a Concrete definition of the Factory Method 
	virtual Car* CreateCar()
	{
		return new Ferrari();
	}
};

int main()
{
	CarFactory *cf1 = new MaruthiFactory();
	CarFactory *cf2 = new FerrariFactory();

	Car *c1 = cf1->CreateCar();
	Car *c2 = cf2->CreateCar();

	c1->DisplayModel(); // Displays "Maruthi" 
	c2->DisplayModel(); // Displays "Ferrari"

	return 0;
}