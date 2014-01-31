// Linked List
/* A Linked List is a dynamic data structure storing a set of sequentially organized 
   items, so called nodes.
   Each node stores:
-	The data item 
-	The link to the next node in the list.
Usually we have two dummy nodes storing the first and last node of the list. The last node next node points to NULL.

   Advantages compared to arrays:
   	- easy growth and shrinking in size over lifetime
  	- high flexibility w.r.t. rearrangement of data items

   Runtime Complexity:
   Insert: O(1)
   Search: O(n) ... n is the length of the list
   Remove: O(n)
*/

struct lnode
{
  int data;
  struct lnode *next; 
};

class list
{
  private:
    struct lnode *first;
    struct lnode *last;
    int count;
   
  public:
    list(): count(0), first(0), last(0) {}

    void appendtotail(int d) // add to end
    {
         struct lnode *n = new lnode();
         n->data = d;
         n->next = NULL;

         if(first == NULL)
         {
           first = n;
           last = n;
         }
         else
         {
           last->next = n;
           last = n;
         }

         count++;
    }
  
    void deletefromtail() // remove from end
    {
        struct lnode *tmp = first;

        if(first == last)
        {
          if(first != NULL)
          {
            delete(tmp);
          }
 
          first = last = NULL;
        } 
	else 
        {
          while(tmp->next != last)
          {
             tmp = tmp->next;
          }

          last = tmp;
		  last->next = NULL;
          delete(tmp->next); 
        }
        
    }
};