#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

/* 
Observer-Pattern
The Observer pattern is a behavioral design pattern that allows an object (an Observer) to watch 
another object (a Subject). The subject and observer to have a publish/subscribe relationship. 
Observers can register to receive events from the Subject. 
The Observer-Pattern is a design pattern in which an object (called the subject) maintains a list 
of its dependents, called observers, and notifies them automatically of any state changes, usually 
by calling one of their methods.
It is mainly used to implement distributed event handling systems. Observer is also a key part in the 
familiar MVC (Model-View-Controller) architectural pattern.

To increase the flexibility, the MVC separates the  GUI (the View) from the data (the Model). 
In MVC you can have different views (= Observers) to the same data (= Model = Subject). If 
something changes in the model, the models inform the observer (= view) and the GUI components 
refresh.

Model: The model manages the behavior and data of the application domain, responds to requests for 
information about its state (usually from the view), and responds to instructions to change state 
(usually from the controller).

View: The view manages the display of information.

Controller: The controller interprets the mouse and keyboard inputs from the user, informing the 
model and/or the view to change as appropriate.
*/

class ObserverInterface
{
public:
	virtual void update() = 0;
};

class Subject // == Model 
{

public:
	void attach(ObserverInterface* observer)
	{
		observers.push_back(observer);
	}
	void detach(ObserverInterface* observer)
	{
		observers.remove(observer);
	}

	void notify()
	{
		list<ObserverInterface*>::iterator it;

		for (it = observers.begin(); it != observers.end(); it++)
		{
			(*it)->update();
		}
	}
private:
	list<ObserverInterface*> observers; // == Views


protected:
	// Durch protected-Konstruktor wird diese Klasse abstrakt 
	Subject() {};

};

class ConcreteSubject : public Subject
{

private:
	string data;

public:
	void setData(string _data) { data = _data; }
	string getData() { return data; }
	ConcreteSubject() : Subject() {}
};

class ConcreteObserver : public ObserverInterface
{
private:
	string name;
	string observerState;
	ConcreteSubject* subject; // Dieses Objekt h�lt die Daten (=notifier) 

public:
	void update()
	{
		observerState = subject->getData();
		cout << "Observer " << name << " hat neuen Zustand: " << observerState << endl;
	}

	void setSubject(ConcreteSubject* obj)
	{
		subject = obj;
	}

	ConcreteSubject* getSubject()
	{
		return subject;
	}

	ConcreteObserver(ConcreteSubject* subj, string n)
	{
		name = n;
		subject = subj;
	}
};

int main()
{
	// Das Objekt h�lt alle Daten (=notfier = subject) 
	ConcreteSubject* subj = new ConcreteSubject();

	ObserverInterface* obs1 = new ConcreteObserver(subj, "A");
	ObserverInterface* obs2 = new ConcreteObserver(subj, "B");

	// Observer(=views) an Subjekt anh�ngen (attachen) 
	subj->attach(obs1);
	subj->attach(obs2);

	// Daten �ndern und Observer informieren (notify) 
	subj->setData("TestData");
	subj->notify();

	return 0;
}
