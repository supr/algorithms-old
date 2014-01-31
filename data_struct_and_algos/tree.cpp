// Binary Tree
/*
A binary tree is a finite set of nodes such that
1.) there is one node called root
2.) there are two disjoint binary trees called the left and right subtree
any node can at most have two children

Pre-Order: Root first, Left child, Right child
Post-Order: Left Child, Right child, root
In-Order: Left child, root, right child. 

        Average	Worst case
Space:	 O(n)	    	O(n)
Search: O(log n)	O(n)
Insert: O(log n)	O(n)
Delete: O(log n)	O(n)   ... is determined by search
*/
class tree
{
private:
	class node *root;
	
public:
	tree(): root(NULL) {}

	bool insert(int val)
	{
		class node *now = root;
		class node *parent = NULL;
		bool is_left_node = false;

		// we look for an empty spot in the tree
		// we want to find the parent not to insert the new node
		while(now)
		{
			parent = now;

			if(val < now->value)
			{
				now = now->left;
				is_left_node = true;
			}
			else if(val > now->value)
			{
				now = now->right;
				is_left_node = false;
			}
			else 
			{
				return false;
			}
		}

		class node *n = new node;
		n->parent = parent;
		n->value = val;

		if(parent == NULL)
		{
			root = n;
		}
		else if(is_left_node)
		{
			parent->left = n;
		}
		else
		{
			parent->right = n;
		}

		return true;
	}

	class node *search(class node *root, int val)
	{
		class node *now = root;

		while(now)
		{
			if(val < now->value)
			{
				return search(now->left, val);
			}
			else if(val > now->value)
			{
				return search(now->right, val);
			}
			else if(now->value == val) 
			{
				return now;
			}
		}

		return NULL;
	}

	bool is_left_child(class node *n)
	{ 
		if(n->parent == 0) 
			return false; // Die Wurzel ist kein Kind 
		else 
			return n->parent->left == n; 
	} 

	class node **get_parent_node(class node *n)
	{
		if(n->parent == 0) 
			return &root; 
		else if(is_left_child(n)) 
			return &n->parent->left; 
		else 
			return &n->parent->right; 
	}

	void swap_nodes(class node *a, class node *b)
	{ 
		std::swap(a->value, b->value);
	}

	class node *get_max(class node *n)
	{ 
		class node *now = n; 
		while(now->right) 
			now = now->right; 
		return now; 
	} 

	bool is_right_child(class node *n)
	{ 
		if(n->parent == 0) 
			return false; // Die Wurzel ist kein Kind 
		else 
			return n->parent->right == n; 
	}

	class node *get_prev_node(class node *now)
	{ 
		if(now->left) 
			return get_max(now->left); 
		else
		{ 
			assert(true);
		}
        return 0; // Wir sind am Anfang angekommen 
	} 

	bool delete_node(int val)
	{
		class node *now = root;
		class node *n = NULL;

		n = search(now, val);
		return remove(n);
	}

	bool remove(class node *n)
	{
		if(n == NULL) // node not found
		{
			return false;
		}
		else
		{
			// only 1 node
			if(!n->left && !n->right)
			{
				*get_parent_node(n) = NULL;
				delete n;
			}
			// only 1 child node
			else if(n->left && !n->right)
			{
				*get_parent_node(n) = n->left;
				n->left->parent = n->parent;
				delete n;
			}
			// only 1 child node
			else if(!n->left && n->right)
			{
				*get_parent_node(n) = n->right;
				n->right->parent = n->parent;
				delete n;
			}
			// 2 child nodes
			else
			{
				class node *other = get_prev_node(n); 
				swap_nodes(n, other); 
				// Löschen des Knoten durch Benutzen von einer 
				// der beiden anderen Methoden 
				remove(other);
			}

			return true;
		}
	}

	unsigned get_max_depth(class node *n)
	{
		if(n == NULL)
		{
			return 0;
		}
		else
		{
			return 1 + std::max(get_max_depth(n->left), get_max_depth(n->right));
		}
	}

	unsigned get_min_depth(class node *n)
	{
		if(n == NULL)
		{
			return 0;
		}
		else
		{
			return 1 + std::min(get_max_depth(n->left), get_max_depth(n->right));
		}
	}

	bool is_balanced()
	{
		return (get_max_depth(root) - get_min_depth(root)) <= 1; 
	}

	unsigned get_height(class node *n)
	{ 
		if(!n) 
			return 0; 
		unsigned left_height = 0, right_height = 0; 

		if(n->left) 
			left_height = get_height(n->left); 
		if(n->right) 
			right_height = get_height(n->right); 

		// Der höchste Unterbaum bestimmt die Gesamthöhe 
		return std::max(left_height, right_height) + 1; 
	}

	bool insert_to_tree(int val, bool left)
	{
		class node *now = root;
		class node *parent = NULL;
		bool is_left_node = false;

		// we look for an empty spot in the tree
		// we want to find the parent not to insert the new node
		while(now)
		{
			parent = now;

			if(val < now->value)
			{
				now = now->left;
				is_left_node = true;
			}
			else if(val > now->value)
			{
				now = now->right;
				is_left_node = false;
			}
			else 
			{
				return false;
			}
		}

		class node *n = new node;
		n->parent = parent;
		n->value = val;

		if(parent == NULL)
		{
			root = n;
		}

		if(left)
		{
			parent->left = n;
		}
		else
		{
			parent->right = n;
		}

		return true;
	}

	class node *add_node(int *arr, int start, int end)
	{
		if (end < start) {
			return NULL;
		}

		int mid = (start + end) / 2;
		class node *n = new node;
		n->value = arr[mid];
		n->left = add_node(arr, start, mid - 1);
		n->right = add_node(arr, mid + 1, end);

		return n;
	}

	void createMinBST(int *arr, int size)
	{
		root = add_node(arr, 0, size);
	}
};