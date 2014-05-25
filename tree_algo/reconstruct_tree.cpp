#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
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

	node *get_most_left_node(node *current) {
		node *prev = current;

		while (current) {
			prev = current;
			current = current->left;
		}

		return prev;
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
	int in_order_traversal[] = { 15, 30, 35, 40, 45, 50, 60, 70, 72, 75, 77, 80 };
	int pre_order_traversal[] = { 50, 30, 15, 40, 35, 45, 70, 60, 80, 75, 72, 77 };
	int post_order_traversal[] = { 15, 35, 45, 40, 30, 60, 72, 77, 75, 80, 70, 50 };
	int level_order_traversal[] = { 50, 30, 70, 15, 40, 60, 80, 35, 45, 75, 72, 77 };

	tree t1;
	t1.create_tree_pre_in_order(pre_order_traversal, in_order_traversal, 0, sizeof(in_order_traversal) / sizeof(int)-1);
}