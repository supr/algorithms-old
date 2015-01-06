

/* 
Question:
You have two singly linked lists that are already sorted, you have to merge them 
and return a the head of the new list without creating any new extra nodes. The 
returned list should be sorted as well

class Node{
    int data;
    Node *next;
}

- suppose, without less of generality that the first element of A is smaller then
the first element of B
- since they are sorted, the first element of A is the smallest of the entire 
collection of elements
- hence it will be the first in the merged list
- so we put the smalles element first and point its "next" pointer to the resulty 
of merging the rest of elements
- return list1 ... because it's the smallest of all elements in list1 and list2

The idea is relative simple, add one list into the other. 
Consider the following conditions:
1. The l1 is empty. Then l2 is the result.
2. current element in l1 > current element in l2, insert current element in l2 before 
current element of l1.
3. current element in l1 < current element in l2, goto the next element in l1 and 
compare again. 
Step 2 and 3 are in the loop, until l2 is empty.

if the lists are unsorted:
- sort both and apply the MergeLists algo: O(n log n) ...sort + O(n) ... merge
- or just splice them and sort the result, there's std::list<T>::splice
- if you know the list length, yeah, you can save some O(n) factor from the overall 
complexity, but O(nlog n) of the sort will still have much bigger effect
*/

Node *MergeLists(Node *list1, Node *list2) {
  if (list1 == NULL) return list2;
  if (list2 == NULL) return list1;

  if (list1->data < list2->data) {
    list1->next = MergeLists(list1->next, list2);
    return list1;
  } else {
    list2->next = MergeLists(list2->next, list1);
    return list2;
  }
}

Node MergeLists(Node list1, Node list2) {
  if (list1 == NULL) return list2;
  if (list2 == NULL) return list1;

  Node head;
  if (list1->data < list2->data) {
    head = list1;
  } else {
    head = list2;
    list2 = list1;
    list1 = head;
  }
  while(list1->next != NULL && list2 != NULL) {
    if (list1->next->data <= list2->data) {
      list1 = list1->next;
    } else {
      Node tmp = list1->next;
      list1->next = list2;
      list2 = tmp;
    }
  } 
  if (list1->next == NULL) list1->next = list2;
  return head;
}