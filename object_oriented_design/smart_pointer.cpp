#include <iostream>
using namespace std;

/* Question:
Write a smart pointer (smart_ptr) class 
*/

template <class T>
class SmartPointer {
private:
	T *ref;
	int *ref_count;
	
public:
	SmartPointer(): ref(NULL) {
		ref_count = new int;
		*ref_count = 0;
	}

	SmartPointer(T *ptr) {
		ref = ptr;
		ref_count = new int;
		*ref_count = 1;
	}
	
	~SmartPointer() {
		ref_count--;
		
		if(ref_count == 0) {
			delete ref;
			delete ref_count;
			ref = NULL;
		}
	}
	
	SmartPointer(const SmartPointer<T> &other) {
		ref = other.ref;
		ref_count = other.ref_count;
		(*ref_count)++;
	}
	
	SmartPointer& operator=(const SmartPointer<T> &other) {
		if(this != &other) {
			ref = other.ref;
			ref_count = other.ref_count;
			(*ref_count)++;
		}
		
		return *this;
	}
	
	void print_debug_infos() {
		cout << "this->ref: " << ref << ", this->ref_count: " << *this->ref_count << endl;
	}
	
	T *operator->() { return ref; }
	T &operator*() { return *ref; }
};

int main() {

	SmartPointer<int> x(new int); // x.pointer: <good> x.reference_count: 1
	x.print_debug_infos();
	{
		SmartPointer<int> y;     // y.pointer: NULL   y.reference_count: -1
		y.print_debug_infos();
		
		y = x;  // x.pointer: <good> x.reference_count: 1
                        // y.pointer: <good> y.reference_count: 2

		x.print_debug_infos(); y.print_debug_infos();
		
		SmartPointer<int>  z;
		z.print_debug_infos();
    	
		x = z;  // x.pointer: NULL                        x.reference_count:  0 (BAD)
    		        // z.pointer: NULL                        z.reference_count: -1
                        // y.pointer: <bad> (it was deleted by x) y.reference_count:  2
        
		x.print_debug_infos(); y.print_debug_infos(); z.print_debug_infos();
	}
}
