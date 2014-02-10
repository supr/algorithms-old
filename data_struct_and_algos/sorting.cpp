#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
1.) A stable sort is one that's guaranteed not to reorder elements with identical keys:

Quick sort: When you don't need a stable sort and average case performance matters more than worst case performance. A quick 
            sort is O(N log N) on average, O(N^2) in the worst case. A good implementation uses O(log N) auxiliary storage in 
			the form of stack space for recursion.

Merge sort: When you need a stable, O(N log N) sort, this is about your only option. The only downsides to it are that it uses 
            O(N) auxiliary space and has a slightly larger constant than a quick sort. There are some in - place merge sorts, 
			but AFAIK they are all either not stable or worse than O(N log N). Even the O(N log N) in place sorts have so much 
			larger a constant than the plain old merge sort that they're more theoretical curiosities than useful algorithms.

Heap sort: When you don't need a stable sort and you care more about worst case performance than average case performance. It's 
           guaranteed to be O(N log N), and uses O(1) auxiliary space, meaning that you won't unexpectedly run out of heap or 
		   stack space on very large inputs.

Insertion sort: When N is guaranteed to be small, including as the base case of a quick sort or merge sort. While 
			    this is O(N ^ 2), it has a very small constant and is a stable sort.

Bubble sort, selection sort : When you're doing something quick and dirty and for some reason you can't just use the standard 
                              library's sorting algorithm. The only advantage these have over insertion sort is being slightly 
							  easier to implement.


2.) Non - comparison sorts: Under some fairly limited conditions it's possible to break the O(N log N) barrier and sort in O(N). 
    Here are some cases where that's worth a try:

Counting sort: When you are sorting integers with a limited range.

Radix sort: When log(N) is significantly larger than K, where K is the number of radix digits.

Bucket sort: When you can guarantee that your input is approximately uniformly distributed.

/*
   Runtime complexity:
   Best case: O(n^2), Average case: O(n^2), Worst case: O(n^2), 
   Additional Memory: O(1)

   Sort the array from left to right, look for a smallest element and swap it first list element
   Look for the second smallest element and swap it with the second list element
*/

void selectionsort(int *a, int length)
{
	int pos = 0;
	int j = 0;
	int min = 0;

	for(int i = 0; i < length-1; i++)
	{
		pos = i;
		min = a[i];

		for(j = i+1; j < length; j++)
		{
			if(a[j] < min)
			{
				min = a[j];
				pos = j;
			}
		}

		if(pos != i)
		{
			swap(a[i],a[pos]);
		}
	}
}

/* Runtime complexity:
   Best case: O(n), Average case: O(n^2), Worst case: O(n^2), 
   Additional Memory: O(1)

   Swap two element next to each other if they are not in the right order
   If there is no swap necessary any more, the array is sorted
*/
void bubblesort(int *a, int length)
{
	int j = 0;
	bool swapped = false;

	for(int i = 0; i < length-1; i++)
	{
		swapped = false;

		for(j = i+1; j < length; j++)
		{
			if(a[j] < a[i])
			{
				swapped = true;
				swap(a[i],a[j]);
			}
		}

		if(!swapped)
		{
			break;
		}
	}
}

void merge(int *a, int *b, int l, int m, int r) 
{ 
	int i = l;
	int j = m+1;
	int k = l;

	while((i <= m) && (j <= r))
	{ 
		if(a[i] < a[j])
		{
			b[k] = a[i++];
		}
		else
		{
			b[k] = a[j++];
		}

		k++;
	}

	while(i <= m)
	{
		b[k++] = a[i++];
	}
	while(j <= r)
	{
		b[k++] = a[j++];
	}
} 

void copy(int *b, int *a, int l, int r) 
{ 
   for (int i = l; i <= r; i++)  
      a[i] = b[i]; 
}

/* Runtime complexity:
   Best case: O(n*log(n)), Average case: O(n*log(n)), Worst case: O(n*log(n)), 
   Additional Memory: O(n)

   Divide the array into 2 sub arrays called left and right
   Sort left half
   Sort right half
   Merge both sub arrays 
*/
void mergesort(int *a, int *b, int l, int r)
{
   /* rekursiver mergesort algorithmus */ 
   if (l < r)//r-1) 
   { 
     int m = (l + r) / 2; 
     mergesort(a,b,l,m); 
     mergesort(a,b,m+1,r); 
     merge(a,b,l,m,r); 
     copy(b,a,l,r); 
   } 
}

/* Runtime complexity:
   Best case: O(n*log(n)), Average case: O(n*log(n)), Worst case: O(n^2), 
   Additional Memory: O(log(n))
*/
void quicksort(int *a, int l, int r)
{
	int m = (l + r) / 2;
	int pivot = a[m];
	int i = l;
	int j = r-1;

	do {
		while(a[i] < pivot) i++; // find left element > pivot
		while(a[j] > pivot) j--; // find right element < pivot

		// if i and j not already overlapped, we can swap
		if(i < j)
		{
			swap(a[i], a[j]);
		}
	} while(i < j);

	// sort left part
	if(l < j)
	{
		quicksort(a, l, j);
	}
	// sort right part
	if(j < r-1)
	{
		quicksort(a, i, r);
	}
}


/* Runtime complexity:
   Best case: O(n*log(n)), Average case: O(n*log(n)), Worst case: O(n*log(n)), 
   Additional Memory: O(1)
*/
class heapsort
{
	private:
		int *arr;
		int count;

	public:
		heapsort(int *a, int length)
		{
			arr = a;
			count = length;
		}

		void makeheap(int c)
		{
			for (int i = 1; i < c; i++)
			{
				int val = arr[i];
				int s = i;
				int f = (s - 1) / 2;

				while (s > 0 && arr[f] < val)
				{
					arr[s] = arr[f];
					s = f;
					f = (s - 1) / 2;
				}
				arr[s] = val;
			}
		}

		void shift(int *a, int l, int r)
		{
			int i = 0;
			int j = 0;
			int x = 0;

			x = a[i];
			i = l;
			j = 2*i + 1; // left node

			if(j < r && a[j+1] < a[j]) j++; 
			// j is the smaller son of i

			while(j <= r && a[j] < x) 
			{
			  a[i]= a[j];
			  i = j;
			  j = 2*i + 1;

			  if(j < r && a[j+1] < a[j]) j++;
			}

			a[i] = x;
		}

		void sort()
		{
			int l,r,tmp,n;

			n = count;

			for(l = (n-2)/2; l >= 0; l--)
			{
				shift(arr, l, n-1);
			}

			for(r = n-1; r > 0; r--)
			{
				tmp = arr[0];
				arr[0] = arr[r];
				arr[r] = tmp;

				shift(arr, 0, r-1);
			}
		}

		void sort2()
		{
			for (int i = count - 1; i > 0; i--)
			{
				swap(arr[i], arr[0]);
				makeheap(i);
			}
		}
};

/* Runtime complexity:
   Best case: O(n), Average case: O(n^2), Worst case: O(n^2), 
   Additional Memory: O(1)

   The first loop increments selects the element to be inserted at the right pos. The second loop swaps the element which
   is selected in the for loop as long as there is not small element to the left.
*/
void insertionsort(int *a, int length)
{
	int i = 0;
	int j = 0;

	for (i = 1; i < length; i++) {
		j = i;
		                // problem if j == 0
		while (j > 0 && a[j - 1] > a[j]) { // loop until the left element is greater than the right element
			swap(a[j], a[j - 1]);
            j--;
		}
	}
}

/* Runtime Complexity: O(n+k) where n is the number of elements in input array and k is the range of input.
   Additional Memory: O(n+k)
*/
void counting_sort(int *a, int n) {
	int *b = new int[n];
	int range = *std::max_element(a, a + n);
	int *count = new int[range + 1];

	// init b array
	for (int j = 0; j < n; j++) {
		b[j] = 0;
	}

	// init count array
	for (int i = 0; i <= range; i++) {
		count[i] = 0;
	}

	// store count of each number
	// input data : 1, 4, 1, 2, 7, 5, 2
	// index: 0  1  2  3  4  5  6  7
    // count: 0  2  2  0  1  1  0  1
	for (int i = 0; i < n; i++) {
		count[a[i]] = count[a[i]] + 1;
	}

	// modify the count array such that each element at each index stores the sum of previous counts
	// index: 0  1  2  3  4  5  6  7
	// count: 0  2  4  4  5  6  6  7
	for (int i = 1; i <= range; i++) {
		count[i] = count[i] + count[i - 1];
	}

	// generate b array
	for (int i = n - 1; i >= 0; i--) {
		b[count[a[i]] - 1] = a[i];
		count[a[i]] = count[a[i]] - 1;
	}

	// Copy the output array b to a, so that it contains sorted numbers
	for (int i = 0; i < n; i++) {
		a[i] = b[i];
	}

	delete[] b;
	delete[] count;
}