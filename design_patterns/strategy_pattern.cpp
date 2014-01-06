#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

/* 
Strategy Pattern
The strategy pattern is a particular software design pattern, whereby algorithms can be selected at 
runtime. Formally speaking, the strategy pattern defines a family of algorithms, encapsulates each 
one, and makes them interchangeable. Strategy lets the algorithm vary independently from clients 
that use it
*/

// Die abstrakte Basis-Klasse f�r alle Sortier-Implementierungen 
class SortStrategy
{

public:
	virtual void sort(int* data, int len) = 0;

protected:
	SortStrategy() {}
};

class UserClass
{
private:
	int* data;
	SortStrategy* sorter;  // Die zu verwendende "Strategie" 

public:
	const int* getData() { return data; }

	void insertValueAt(int pos, int value)
	{
		if (pos < 10000 && pos >= 0)
			data[pos] = value;
	}

	// Hier m�ssen wir jetzt der Klasse auch eine Sortierstrategie �bergeben 
	UserClass(SortStrategy* s)
	{
		data = new int[10000];
		sorter = s;
	}

	~UserClass()
	{
		delete[] data;
	}


	void sort()
	{
		sorter->sort(data, 10000);
	}

	// Hier kann man jetzt eine neue "Strategie" angeben, mit der sortiert werden soll 
	void changeStrategy(SortStrategy* s)
	{
		sorter = s;
	}
};

class QuickSort : public SortStrategy
{
public:
	QuickSort()  {}

	void sort(int* data, int len) {
		// Hier steht dann die Implementierung des Quicksort-Algorithmus 
	}
};

class ShellSort : public SortStrategy
{
public:
	ShellSort() {}

	void sort(int* data, int len) {
		// Hier steht dann die Implementierung des Shellsort-Algorithmus 
	}
};

int main()
{
	SortStrategy* s = new ShellSort();
	UserClass* c = new UserClass(s);
	c->sort(); // mit Shellsort sortieren 

	//Algorithmus wechseln 
	c->changeStrategy(new QuickSort());
	c->sort(); // jetzt wird mit Quicksort sortiert 

	// in C++ m�ssen wir selbst allozierte Speicherbereiche auch wieder freigeben: 
	delete s;
	delete c;

	// ACHTUNG: Beim Aufruf von "c->changeStrategy(new QuickSort());" haben wir uns jedoch nicht 
	// die Speicheradresse des neuen QuickSort-Objekt 
	// gemerkt und k�nnen es somit auch nicht selbst wieder freigeben. D. h., hier w�rde ein Memory 
	// Leak entstehen, wenn das Programm noch l�nger laufen w�rde.

	return 0;
}