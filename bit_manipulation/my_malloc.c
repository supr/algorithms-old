#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Question:
Implement a memory allocator in C.
*/

#define HEAP_MEM_SIZE 200
#define MEMORY_AVAILABLE 1 
#define MEMORY_USED 0 

typedef struct chunk_header {
	struct chunk_header *next; // next pointer on free list
  	unsigned int size;               // the size of this chunk
  	bool is_available;         // indicates if this chunk is MEMORY_AVAILABLE or MEMORY_USED
}chunk_header_t;

chunk_header_t *chunk_header_begin;
static char buffer[HEAP_MEM_SIZE];
unsigned int heap_size;

void init() {
	heap_size = HEAP_MEM_SIZE;
	chunk_header_begin = (chunk_header_t*)&buffer;
	chunk_header_begin->next = NULL;
	chunk_header_begin->size = heap_size;
	chunk_header_begin->is_available = MEMORY_AVAILABLE;
}

void init_next_chunk(chunk_header_t *curr, unsigned int bytes) {
	heap_size -= bytes;
	curr->next = NULL;
	curr->size = heap_size;
	curr->is_available = MEMORY_AVAILABLE;
}

void *my_malloc(unsigned int nbytes) {
	static bool init_flag = false;
	
	if(!init_flag) {
		init();
		init_flag = true;
	}

	int alloc_size = nbytes + sizeof(chunk_header_t);	
	chunk_header_t *curr = chunk_header_begin;

	while(curr) {
		if(curr->is_available && curr->size >= alloc_size) {
			curr->is_available = MEMORY_USED;
			curr->size = alloc_size;
			curr->next = curr + alloc_size;
			
			init_next_chunk(curr->next, alloc_size);
		
			// return memory region
			curr = curr + sizeof(chunk_header_t);
			return curr;
		}
		
		curr = curr->next;
	}
	
	return NULL;
}

void my_free(void *firstbyte) {
	chunk_header_t *mem = (chunk_header_t*)firstbyte - sizeof(chunk_header_t);
	chunk_header_t *curr = chunk_header_begin;

	while (curr) {
		if (curr == mem) {
			heap_size += curr->size;

			// Mark the block as being available
			curr->is_available = MEMORY_AVAILABLE;
			break;
		}

		curr = curr->next;
	}
	
	firstbyte = NULL;
}

void print_heap_allocations() {
	chunk_header_t *curr = chunk_header_begin;

	printf("\n\tHeapsize\tChunksize\tAvailable\tMemory-Ptr");

	while (curr) {
		void *mem_ptr = curr + sizeof(chunk_header_t);
		printf("\n\t%d\t\t%d\t\t%d\t\t%p", heap_size, curr->size, curr->is_available, mem_ptr);
		curr = curr->next;
	}
	
	printf("\n");
}

int main() {
	char *mem1 = (char*)my_malloc(20); 
	if(!mem1) {
		fprintf(stderr, "Error allocating memory to mem1.\n");
    		return -1;
	}
    	memset (mem1,'x',19); 
    	mem1[19] = '\0'; 
    
    	print_heap_allocations();
    
    	char *mem2 = (char*)my_malloc(20); 
    	if(!mem2) {
		fprintf(stderr, "Error allocating memory to mem2.\n");
    		return -1;
	}
    	memset (mem2,'y',19); 
    	mem2[19] = '\0'; 
    
    	print_heap_allocations();
    
    	char *mem3 = (char*)my_malloc(20); 
    	if(!mem3) {
    		fprintf(stderr, "Error allocating memory to mem3.\n");
    		return -1;
    	}
    	memset (mem3,'z',19); 
    	mem3[19] = '\0'; 
  
    	print_heap_allocations();
    
  	my_free(mem2);
  	
  	print_heap_allocations();
  	
  	char *mem4 = (char*)my_malloc(20);
  	if(!mem4) {
		fprintf(stderr, "Error allocating memory to mem4.\n");
    		return -1;
	} 
    	memset (mem4,'a',20); 
   	mem4[19] = '\0';
        
    	print_heap_allocations();
    
    	printf("should be 19 x sein: %s\n", mem1); 
    	printf("should be 19 a sein: %s\n", mem4); 
    	printf("should be 19 z sein: %s\n", mem3);
	
	return 0;
}
