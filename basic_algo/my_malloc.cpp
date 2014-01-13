#include <stdio.h> 

/* Question:
implement your own malloc and free for application x, which should control the heap memory usage of the application x.
*/

#define MEMORY_AVAILABLE 1 
#define MEMORY_USED 0 
#define HEAP_MEMORY 1000 

char raw_memory[HEAP_MEMORY];
typedef struct memory_chunk heap_memory;

struct memory_chunk {
	heap_memory *next;
	int size;
	int is_available;
	void *memory;
};

int heap_size = HEAP_MEMORY;
heap_memory mlist;

int init_memory_mgr() {
	heap_size = HEAP_MEMORY;
	mlist.next = NULL;
	mlist.size = heap_size;
	mlist.is_available = MEMORY_AVAILABLE;
	mlist.memory = raw_memory;
	return 1;
}


void *my_malloc(int size) {
	if (size <= 0) {
		printf("ERROR\n");
		return NULL;
	}

	heap_memory *temp = &mlist;
	int alloc_size = size + sizeof(heap_memory);

	while (temp) {
		if (temp->is_available == MEMORY_AVAILABLE) {
			if (temp->size >= alloc_size) {
				void * allocated_memory = (heap_memory*)(temp);
				printf("\ntemp=0x%x\n", temp);
				temp->size = size;
				temp->is_available = MEMORY_USED;
				temp->memory = (temp)+sizeof(temp->size) + sizeof(temp->is_available);
				temp->next = (heap_memory*)temp->memory + size;
				heap_size -= size;

				heap_memory *new_memory_ptr = temp->next;
				new_memory_ptr->is_available = MEMORY_AVAILABLE;
				new_memory_ptr->size = heap_size;
				return temp->memory;
			}
		}
		temp = temp->next;
	}//while 

	printf("\nNo Memory Available\n");
	return NULL;
}

// not finished
void my_free(void *firstbyte) {
	heap_memory *memory_ptr = (heap_memory*)firstbyte;

	heap_memory *prev = &mlist;
	heap_memory *curr = &mlist;

	while (curr) {
		if (curr->memory == memory_ptr) {
			heap_size += curr->size;

			if (curr == &mlist) {
				curr->next = NULL;
				curr->size = heap_size;
			}
			else {
				prev->next = curr->next;
			}

			curr->memory = NULL;

			// Mark the block as being available
			curr->is_available = MEMORY_AVAILABLE;
			break;
		}

		prev = curr;
		curr = curr->next;
	}

	firstbyte = NULL;
	return;
}

void print_heap_allocations() {
	heap_memory *temp = &mlist;

	printf("\n\tSize\tMemory-Ptr");

	while (temp) {
		printf("\n\t%d\t%x ", temp->size, temp->memory);
		temp = temp->next;
	}
	printf("\n");
}

int main()
{
	// your code goes here

	init_memory_mgr();
	print_heap_allocations();

	void *m1;
	m1 = my_malloc(10);
	printf("\nallocated 10 bytes:0x%x\n", m1);
	print_heap_allocations();

	void *m2;
	m2 = my_malloc(20);
	printf("\nallocated 10 bytes:0x%x\n", m2);
	print_heap_allocations();

	void *m3;
	m3 = my_malloc(10);
	printf("\nallocated 10 bytes:0x%x\n", m3);
	print_heap_allocations();

	my_free(m3);
	my_free(m2);
	my_free(m1);

	print_heap_allocations();

	return 0;
}