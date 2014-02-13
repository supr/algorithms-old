// Stack
/* The Queue is a one-dimensional structures with LIFO (last in first out) ordering
   supports two types of basic operations:
 - push (val): inserting one element with value val at the beginning of the stack
 - pop: removing one element from the beginning of the stack and returning its value*/
 
   Runtime Complexity:
   Insert: O(1)
   Delete: O(1)

/* LIFO - Last in First out*/
template <class T>
class stack
{
private:
	struct node<T> *first;
	struct node<T> *last;
	int size;

public:
	stack(): size(0), first(NULL), last(NULL)
	{
	}

	void push(T element)
	{
		struct node<T> *n = new node<T>();
		n->data = element;
		n->next = NULL;
		struct node<T> *tmp = first;

		// empty list
		if(first == NULL)
		{
			first = n;
			last = n;
		}
		else // we add a new element at the beginning of the list
		{
			first = n;
			first->next = tmp;
		}

		size++;
	}

	T pop()
	{
		T data;
		node<T> *tmp = first;

		// empty list
		if(first == NULL)
		{
			throw("pop from empty stack");		
		}
		else // we remove an element from the beginning of the list
		{
			data = first->data;
			first = first->next;
			
			if(first == NULL)
			{
				last = NULL;
			}

		    size--;

			delete(tmp);
			return data;
		}
	}

	int getsize()
	{
		return size;
	}
};


