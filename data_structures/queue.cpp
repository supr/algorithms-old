/* Queue
   The Queue is a one-dimensional structures with FIFO (first in first out) ordering
   supports two types of basic operations:
 - insert (enqueue): inserting one element with value val at the beginning of the queue
 - remove (dequeue): removing one element from the end of the queue and returning its   
   Value

Runtime Complexity:
- Insert: O(1)
- Delete: O(1)
*/

template <class T>
struct node
{
	T data;
	struct node *next;
};

/* FIFO - First in First out */
template <class T>
class queue
{
private:
	struct node<T> *first;
	struct node<T> *last;
	int size;

public:
	queue(): size(0), first(NULL), last(NULL)
	{
	}

	void enqueue(T element)
	{
		struct node<T> *n = new node<T>();
		n->data = element;
		n->next = NULL;

		// empty list
		if(first == NULL)
		{
			first = n;
			last = n;
		}
		else // we add a new element at the end of the list
		{
			last->next = n;
			last = n;
		}

		size++;
	}

	T dequeue()
	{
		T data;
		node<T> *tmp = first;

		// empty list
		if(first == NULL)
		{
			throw("Dequeue from empty queue");		
		}
		else // we remove an element from the beginning of the list
		{
			data = first->data;
			first = first->next; // the node after the first one becomes the new first
			
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
