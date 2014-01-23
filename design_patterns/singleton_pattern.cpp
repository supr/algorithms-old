#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

/* Singleton Pattern
the singleton pattern is a design pattern used to implement the mathematical concept of a singleton, by
restricting the instantiation of a class to one object. This is useful when exactly one object is needed
to coordinate actions across the system. The concept is sometimes generalized to systems that operate
more efficiently when only one object exists, or that restrict the instantiation to a certain number of
objects.
*/

class Singleton
{
private:
	static Singleton *inst_;

protected:
	Singleton() {}

	//Copy-Konstruktor: Hierdurch werden Kopien dieses Objektes verhindert (da protected) 
	Singleton(const Singleton& other) {}

	Singleton& operator= (const Singleton&) {}

public:
	~Singleton() {
		delete inst_;
	}

	static Singleton *get_Instance() {
		if (inst_ == NULL)
		{
			inst_ = new Singleton;
		}

		return inst_;
	}

	void test() {
		cout << "test" << endl;
	}
};

Singleton* Singleton::inst_ = 0; // initialize pointer

class Singleton2
{

public:
	static Singleton2& Instance()
	{
		//das einzige Objekt dieser Klasse erzeugen und als Referenz zur�ckgeben 
		static Singleton2 instance;
		return instance;
	}

	void doSomething() { }


protected:
	Singleton2() {}

	//Copy-Konstruktor: Hierdurch werden Kopien dieses Objektes verhindert (da protected) 
	Singleton2(const Singleton2& other) {}

};

int main()
{
	Singleton *p1 = Singleton::get_Instance();
	p1->test();

	return 0;
}
