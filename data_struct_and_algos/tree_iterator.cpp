#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <bitset>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <limits>
using namespace std;

typedef struct node {
	struct node *left;
	struct node *right;
	struct node *parent;
	int value;
}node;

class tree {
private:
	node *root;

public:
	class tree_iterator {
	private:
		struct tree *ptree;
		struct node *curr;
		struct node *prev;

	public:
		tree_iterator(tree *ptree_): ptree(ptree_) {}

		node *get_curr() {
			return curr;
		}

		node *get_root() {
			return ptree->get_root();
		}

		void tree_iterator_begin(node *start) {
			prev = NULL;
			curr = start;
		}

		void tree_iterator_end() {
			curr = NULL;
		}

		bool operator== (tree_iterator &it) {
			return this->get_curr() == it.get_curr();
		}

		bool operator!= (tree_iterator &it) {
			return get_curr() != it.get_curr();
		}

		node operator* () {
			return *this->get_curr();
		}

		// inorder_traversal
		tree_iterator &get_next_node() {
			if(curr) {
				node *tmp;

				// Found right children -> return 1st inorder node on right
				if (curr->parent == NULL || curr->right != NULL) {
					tmp = leftMostChild(curr->right);
				} else {
					// Go up until we’re on left instead of right (case 2b)
					while ((tmp = curr->parent) != NULL) {
						if (tmp->left == curr) {
							break;
						}
						curr = tmp;
					}
				}
				curr = tmp;
			}
			return *this;
		}

		node *leftMostChild(node *e) {
			if (e == NULL) return NULL;

			while (e->left != NULL) 
				e = e->left;
			
			return e;
		}
	};

public:
	tree(): root(NULL) {}

	node *get_root() {
		return root;

	}

	class tree_iterator begin(node *start) {
		class tree_iterator it(this);
		it.tree_iterator_begin(start);
		return it;
	}

	class tree_iterator end() {
		class tree_iterator it(this);
		it.tree_iterator_end();
		return it;
	}

	void insert(int value) {
		struct node *curr = root;
		struct node *prev = NULL;
		struct node *tmp = new node;
		tmp->value = value;
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->parent = NULL;

		if(root == NULL) {
			root = tmp;
		}
		else {
			while(curr) {
				if(value < curr->value) {
					prev = curr;
					curr = curr->left;
				}
				else {
					prev = curr;
					curr = curr->right;
				}
			}

			curr = prev;

			if(value < curr->value) {
				curr->left = tmp;	
			}
			else {
				curr->right = tmp;
			}

			tmp->parent = prev;
		}
	}

	int search_index(int  in_order[], int start, int end, int value) {
		for(int i = start; i <= end; i++) {
			if(in_order[i] == value) {
				return i;
			}
		}

		return -1;
	}

	node *create_node(int data) {
		node *n = new node;
		n->left = NULL;
		n->right = NULL;
		n->parent = NULL;
		n->value = data;
		return n;
	}

	node *create_tree_pre_in_order(int pre_order[], int in_order[], int start, int end) {
		static int pre_index = 0;

		if(start > end) {
			return NULL;
		}

		/* Pick current node from Preorder traversal using preIndex
		and increment preIndex */
		int root_val = pre_order[pre_index++];
		node *n = create_node(root_val);
		if(pre_index == 1) {
			root = n;
		}

		/* If this node has no children then return */
		if(start == end) {
			return n;
		}
		
		/* Else find the index of this node in Inorder traversal */
		int index = search_index(in_order, start, end, root_val);
		if(index == -1) {
			return NULL;
		}

		/* Using index in Inorder traversal, construct left and
		right subtress */
		n->left = create_tree_pre_in_order(pre_order, in_order, start, index-1);
		n->right = create_tree_pre_in_order(pre_order, in_order, index+1, end);

		return n;
	}

	node *create_tree_in_post_order(int in_order[], int post_order[], int start, int end) {
		static int post_index = end;

		if(start > end) {
			return NULL;
		}

		int root_val = post_order[post_index--];
		node *n = create_node(root_val);
		if(post_index == end-1) {
			root = n;
		}

		if(start == end) {
			return n;
		}

		int index = search_index(in_order, start, end, root_val);
		if(index == -1) {
			return NULL;
		}

		n->left = create_tree_in_post_order(in_order, post_order, start, index-1);
		n->right = create_tree_in_post_order(in_order, post_order, index+1, end);

		return n;
	}

	node *create_tree_in_level_order(int in_order[], int level_order[], int start, int end) {
		static int level_index = 0;

		if(start > end) {
			return NULL;
		}

		int root_val = level_order[level_index++];
		node *n = create_node(root_val);
		if(level_index == 1) {
			root = n;
		}

		if(start == end) {
			return n;
		}

		int index = search_index(in_order, start, end, root_val);
		if(index == -1) {
			return NULL;
		}

		n->left = create_tree_in_level_order(in_order, level_order, start, index-1);
		n->right = create_tree_in_level_order(in_order, level_order, index+1, end);

		return n;
	}

	// depth first search
	void pre_order_traversal_recursive(node *n) {
		if(n != NULL) {
			cout << n->value;
			pre_order_traversal_recursive(n->left);
			pre_order_traversal_recursive(n->right);
		}
	}

	void pre_order_traversal_iterative(node *n) {
		stack<node*> stk;
		stk.push(n);

		while(!stk.empty()) {
			node *tmp = stk.top();
			stk.pop();

			cout << tmp->value << endl;

			if(tmp->left) {
				stk.push(tmp->left);
			}

			if(tmp->right) {
				stk.push(tmp->right);
			}
		}
	}

	void in_order_traversal_recursive(node *n) {
		if(n != NULL) {
			in_order_traversal_recursive(n->left);
			cout << n->value;
			in_order_traversal_recursive(n->right);
		}
	}

	void in_order_traversal_iterative(node *n) {
		if (!n) return;
		stack<node*> stk;
		node *curr = n;

		while(!stk.empty() || curr) {
			if(curr != NULL) {
				stk.push(curr);
				curr = curr->left;
			}
			else {
				node *tmp = stk.top();
				stk.pop();

				cout << tmp->value << endl;

				curr = tmp->right;
			}
		}
	}

	void post_order_traversal_recursive(node *n) {
		if(n != NULL) {
			post_order_traversal_recursive(n->left);
			post_order_traversal_recursive(n->right);
			cout << n->value;
		}
	}

	void post_order_traversal_iterative(node *n) {
		stack<node*> stk;
		stack<node*> output;
		stk.push(n);

		while(!stk.empty()) {
			node *tmp = stk.top();
			stk.pop();
			output.push(tmp);

			if(tmp->left) {
				stk.push(tmp->left);
			}
			if(tmp->right) {
				stk.push(tmp->right);
			}
		}

		while(!output.empty()) {
			node *tmp = output.top();
			output.pop();

			cout << tmp->value << endl;
		}
	}

	// breath first search
	void level_order_traversal_iterative(node *n) {
		if (!n) return;
		queue<node*> s;  
		s.push(n);  

		while (!s.empty()) {  
			node *curr = s.front(); 
 
			cout << curr->value << endl;

			s.pop(); 
			if (curr->left)  // first put left child on to the queue because its FIFO
				s.push(curr->left);  
			if (curr->right)  
				s.push(curr->right);  
		}
	}

	node *get_in_order_predecessor(node *current) {
			if(current) {
				node *tmp = current;

				if(current->parent == NULL || current->left != NULL) {
					tmp = current->left;
					while(tmp->right) {
						tmp = tmp->right;
					}
				}
				else {
					while(tmp = current->parent) {
						if(current == tmp->right) {
							break;
						}
						current = tmp;
					}
				}

				current = tmp;
			}

			return current;
		}

	node *get_pre_order_successor(node *current) {
		static stack<node*> s;
		bool found_next_node = false;

		if(current)  {
			node *tmp = current;

			if(!s.empty()) {
				tmp = s.top();
				s.pop();
				found_next_node = true;
			}
			
			if(tmp->right) {
				s.push(tmp->right);
			    found_next_node = true;
			}
			if(tmp->left) {
				s.push(tmp->left);
			    found_next_node = true;
			}

			if(!found_next_node)
				return NULL;

			current = tmp;
			return current;
		}

		return NULL;
	}

	node *get_level_order_successor(node *current) {
		static queue<node*> q;
		bool found_next_node = false;

		if(current)  {
			node *tmp = current;

			if(!q.empty()) {
				tmp = q.front();
				q.pop();
				found_next_node = true;
			}

			if(tmp->left) {
				q.push(tmp->left);
			    found_next_node = true;
			}
			if(tmp->right) {
				q.push(tmp->right);
			    found_next_node = true;
			}

			if(!found_next_node)
				return NULL;

			current = tmp;
			return current;
		}

		return NULL;
	}

	node *create_tree_from_pre_order(int pre_order[], int start, int end) {
		static int index = 0;

		if(end < start)
			return NULL;

		node *n = create_node(pre_order[index++]);
		if(index == 1) {
			root = n;
		}

		int i = 0;
		for(i = start; i <= end; i++) {
			if(pre_order[i] > pre_order[start])
				break;
		}

		n->left = create_tree_from_pre_order(pre_order, start+1, i-1);
		n->right = create_tree_from_pre_order(pre_order, i, end);
		
		return n;
	}

	node *create_tree_from_post_order(int post_order[], int start, int end) {
		static int index = end;
		static int end_ = end;

		if(end < start)
			return NULL;

		node *root_n = create_node(post_order[index--]);
		if(index == end_-1) {
			root = root_n;
		}

		int i = 0;
		for(i = end; i >= 0; i--) {
			if(post_order[i] < post_order[end])
				break;
		}

		root_n->right = create_tree_from_post_order(post_order, i+1, end-1);
		root_n->left = create_tree_from_post_order(post_order, start, i);

		return root_n;
	}

	node *create_MST(int in_order[], int start, int end) {
		static int index = 0;

		if(end < start)
			return NULL;

		int mid = (start + end) / 2;
		
		node *n = create_node(in_order[mid]);
		if(index++ == 0) {
			root = n;
		}

		n->left = create_MST(in_order, start, mid-1);
		n->right = create_MST(in_order, mid+1, end);

		return n;
	}

	node *findCP(node *root, int n1, int n2) {
	  if (root == NULL)
	   return NULL;

	  node *l = findCP(root->left, n1, n2);
	  node *r = findCP(root->right, n1, n2);
	  
	  if(root->value == n1 ||root->value == n2)
	    return root;
	  
	  if(l!=NULL && r!=NULL)
	   return root;
	  
	  else return (l==NULL)? r:l;
	}

	int get_k_largest_element(int k) {
		node *curr = root;
		std::stack<node*> stk;
		int counter = 0;

		while(!stk.empty() || curr) {
			if(curr) {
				stk.push(curr);
				curr = curr->right;
			}
			else {
				node *tmp = stk.top();
				stk.pop();

				counter++;

				if(counter == k) {
					return tmp->value;
				}

				curr = tmp->left;
			}
		}
	}

	unsigned int get_min(node *n) {
		if(!n) {
			return NULL;
		}
		else {
			return 1 + std::min(get_min(n->left), get_min(n->right)); 
		}
	}

	typedef struct node_info {
		node_info(node *n1, int h): n(n1), height(h) {}
		node *n;
		int height;
	}node_info;

	void add_to_list(std::vector<std::list<node_info>> &l, node *n, int height) {
	  std::vector<std::list<node_info>>::iterator it;
	  std::list<node_info>::iterator it2;
	  bool found = false;

	  for(it = l.begin(); it != l.end(); it++) {
		it2 = (*it).begin();

		if(it2->height == height) {
		  node_info t(n, height);
		  it->push_back(t);
		  found = true;
		  break;
		}
	  }

	  if(!found) {
		node_info t(n, height);
		std::list<node_info> l2;
		l2.push_back(t);
		l.push_back(l2);
	  }  
	}

	// save all nodes of hight h1 into a std::list
    bool get_list_nodes_of_height(std::list<node_info> &out, int h1) {
	  typedef struct n_info {
		n_info(node *nn, int h): n(nn), height(h) {}
		node *n;
		int height;	 
	  }n_info;

	  node *n = get_root();
	  std::vector<std::list<node_info>> l;
	  std::queue<n_info> s;
	  int height = 0;

	  s.push(n_info(n, height));

	  while(!s.empty()) {
		n_info nf = s.front();

		height = nf.height;
		node *t = nf.n;

		add_to_list(l, t, height);

		s.pop();

		if(t->right) {
		  s.push(n_info(t->right, height+1));
		}
		if(t->left) {
		  s.push(n_info(t->left, height+1));
		}
	  }

	  std::list<node_info>::iterator it2 = l[h1].begin();
	  if(it2->height == h1) {
		  out = l[h1];
		  return true;
	  }

	  return false;
	}

	void get_siblings(node *n, std::list<node_info> &l) {
		stack<node_info> s;
		
		s.push(node_info(n, 0));

		while(!s.empty()) {
			node_info nf = s.top();
			s.pop();

			l.push_back(nf);
			node *r = nf.n;

			if(r->left) {
				s.push(node_info(r->left, 0));
			}
			if(r->right) {
				s.push(node_info(r->right, 0));
			}
		}
	}

	void first_first_k_elements(node *root, int k, vector<int> &arr) {
		stack<node*> stk;
		stk.push(root);
		int counter = 0;

		while(!stk.empty() || root) {
			if(root) {
				stk.push(root);
				root = root->left;
			}
			else {
				node *n = stk.top();
				stk.pop();

				counter++;
				if(counter <= k) {
					arr.push_back(n->value);
				}
				else {
					break;
				}

				root = n->right;
			}
		}
	}

	node *get_common_parent(node *root, int key1, int key2) {
		while (root != NULL) {
			int key = root->value;
			if (key < key1 && key < key2)
				root = root->right;
            else if (key > key1 && key > key2)
				root = root->left;
            else
                return root;
        }

        return NULL;
    }

	/*
	Alternatively, you could follow a chain in which p and q are on the same side. That is, if p and q are both on the left of the node, 
	branch left to look for the common ancestor. When p and q are no longer on the same side, you must have found the first common ancestor.
	*/
	node *common_ancestor(node *root, node *p, node *q) {
		if (covers(root->left, p) && covers(root->left, q))
			return common_ancestor(root->left, p, q);
		if (covers(root->right, p) && covers(root->right, q))
			return common_ancestor(root->right, p, q);
		return root;
	}

	bool covers(node *root, node *p) { // is p a child of root?
		if (root == NULL) return false;
		if (root == p) return true;
		return covers(root->left, p) || covers(root->right, p);
	}

	// For any node r, we know the following:
	// 1. If p is on one side and q is on the other, r is the first common ancestor.
	// 2. Else, the first common ancestor is on the left or the right side.
	// So, we can create a simple recursive algorithm called search that calls search(left side) and search(right side) looking at how many nodes (p or q) are placed from the left side and from the right side of the current node. If there are two nodes on one of the sides, then we have
	// to check if the child node on this side is p or q (because in this case the current node is the
	// common ancestor)  If the child node is neither p nor q, we should continue to search further (starting from the child)

	// If one of the searched nodes (p or q) is located on the right side of the current node, then the 
	// other node is located on the other side  Thus the current node is the common ancestor
	/*static int TWO_NODES_FOUND = 2;
	static int ONE_NODE_FOUND = 1;
	static int NO_NODES_FOUND = 0;

	// Checks how many “special” nodes are located under this root
	int covers(TreeNode root, TreeNode p, TreeNode q) {
		int ret = NO_NODES_FOUND;
		if (root == null) return ret;
		if (root == p || root == q) ret += 1;
		ret += covers(root.left, p, q);
		if(ret == TWO_NODES_FOUND) // Found p and q
			return ret;
	    return ret + covers(root.right, p, q);
	}

	TreeNode commonAncestor(TreeNode root, TreeNode p, TreeNode q) {
		if (q == p && (root.left == q || root.right == q)) return root;
		int nodesFromLeft = covers(root.left, p, q); // Check left side
		if (nodesFromLeft == TWO_NODES_FOUND) {
			if(root.left == p || root.left == q) return root.left;
			else return commonAncestor(root.left, p, q);
		} else if (nodesFromLeft == ONE_NODE_FOUND) {
			if (root == p) return p;
			else if (root == q) return q;
		}
		int nodesFromRight = covers(root.right, p, q); // Check right side
		if(nodesFromRight == TWO_NODES_FOUND) {
			if(root.right == p || root.right == q) return root.right;
			else return commonAncestor(root.right, p, q);
		} else if (nodesFromRight == ONE_NODE_FOUND) {
			if (root == p) return p;
			else if (root == q) return q;
		}
		if (nodesFromLeft == ONE_NODE_FOUND &&
			nodesFromRight == ONE_NODE_FOUND) return root;
		else return null;
	}
	*/

	// find the distance between 2 values in a binary search tree. Node will have value, left node and right node 
	// We can do a preorder traversal on the binary tree. 
    // Time compexity O(N), space complexity, O(log(n))
	int findDistance(node *root, int val1, int val2) {
		// check if the tree is empty or not
		if(root == NULL)
		{
			return -1;
		}

		// check if the two values are equal or not, if they are
		// then the distance between the two is obviously zero
		if(val1 == val2)
			return 0;

		// have a stack to hold the nodes for back traversal
		std::stack<node*>  stack;

		// For simplifying our code, we will make val1 < val2
		if(val2 < val1)
		{
			val1 = val1 + val2;
			val2 = val1 - val2;
			val1 = val1 - val2;
		}

		// initial distance betwen nodes is -1
		int distance = -1;

		while(!stack.empty() || root != NULL)
		{
			// traverse to the left of the subtree at root
			if(root != NULL)
			{
				if(root->value == val1)
					distance = 0;

				// if value of this node = val2, then we are done
				// return distance calculated so far
				else if(root->value == val2)
					return distance;

				stack.push(root);
				root = root->left;

				// this node might be on the path between val and val2
				// increment distance
				++distance;
			}
			// else go right
			else
			{
				root = stack.top();
				stack.pop();

				// this node is not on the path between val and val2
				// decrement distance
				--distance;

				root = root->right;
			}
		}
		return distance;
	}
};

int main() {
   int in_order_traversal[] = {15,30,35,40,45,50,60,70,72,75,77,80};
   int pre_order_traversal[] = {50,30,15,40,35,45,70,60,80,75,72,77};
   int post_order_traversal[] = {15,35,45,40,30,60,72,77,75,80,70,50};
   int level_order_traversal[] = {50,30,70,15,40,60,80,35,45,75,72,77};
   
   tree tt;
   tt.create_tree_pre_in_order(pre_order_traversal, in_order_traversal, 0, sizeof(in_order_traversal)/sizeof(int)-1);
   vector<int> vec3;
   tt.first_first_k_elements(tt.get_root(), 5, vec3);
   

   tree t;
   t.insert(4);
   t.insert(3);
   t.insert(5);

   t.in_order_traversal_recursive(t.get_root());
   cout << '\n';
   t.pre_order_traversal_recursive(t.get_root());
   cout << '\n';
   t.post_order_traversal_recursive(t.get_root());
}