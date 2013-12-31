#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <sstream>
#include <stack>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <queue>
#include <map>
#include <list>
#include <vector>
#include <cstdlib>
#include <limits>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <array>
#include <thread>
#include <future>
#include <set>
#include <utility>
#include <limits>
using namespace std;

template<class T>
class Tree{
public:
	struct Node{
		Node*parent, *left, *right;
		T value;

		explicit Node(const T&value) :
			parent(0), left(0), right(0), value(value){}
	};

	Node*root;
public:
	Tree() :root(0){}

	bool is_empty()const{
		return !root;
	}

	// ------------------------------------------------------------------ //

private:
	static bool is_left_child(const Node*node){
		if (node->parent == 0)
			return false; // Die Wurzel ist kein Kind
		else
			return node->parent->left == node;
	}

	static bool is_right_child(const Node*node){
		if (node->parent == 0)
			return false; // Die Wurzel ist kein Kind
		else
			return node->parent->right == node;
	}

	Node**get_parent_ptr(Node*node){
		if (node->parent == 0)
			return &root;
		else if (is_left_child(node))
			return &node->parent->left;
		else
			return &node->parent->right;
	}

	static std::string format_label(const Node*node){
		if (node){
			std::ostringstream out;
			out << node->value;
			return out.str();
		}
		else
			return "";
	}

	static unsigned get_height(const Node*node){
		if (!node)
			return 0;
		unsigned left_height = 0, right_height = 0;

		if (node->left)
			left_height = get_height(node->left);
		if (node->right)
			right_height = get_height(node->right);

		// Der h�chste Unterbaum bestimmt die Gesamth�he
		return std::max(left_height, right_height) + 1;
	}

	static unsigned get_width(const Node*node){
		if (!node)
			return 0;
		unsigned left_width = 0, right_width = 0;

		if (node->left)
			left_width = get_width(node->left);
		if (node->right)
			right_width = get_width(node->right);

		return left_width + format_label(node).length() + right_width;
	}

	static void dump_spaces(std::ostream&out, unsigned count){
		for (unsigned i = 0; i < count; ++i)
			out.put(' ');
	}

	static void dump_line(std::ostream&out, const Node*node, unsigned line){
		if (!node)
			return;
		if (line == 1){
			// Die Wurzel des Unterbaums soll ausgegeben werden
			dump_spaces(out, get_width(node->left));
			out << format_label(node);
			dump_spaces(out, get_width(node->right));
		}
		else{
			// In beiden Unterb�umen sind die Wurzeln um eins niedriger und darum ver�ndert
			// sich die Zeilennummerierung.
			dump_line(out, node->left, line - 1);
			dump_spaces(out, format_label(node).length());
			dump_line(out, node->right, line - 1);
		}
	}

	static void dump_node(std::ostream&out, const Node*node){
		for (unsigned line = 1, height = get_height(node); line <= height; ++line){
			dump_line(out, node, line);
			out.put('\n');
		}
		out.flush();
	}

public:
	void dump(std::ostream&out)const{
		dump_node(out, root);
	}

private:
	bool is_wellformed(Node*node){
		if (node == 0)
			return true;
		if (*get_parent_ptr(node) != node)
			return false;
		if (!is_wellformed(node->left))
			return false;
		if (!is_wellformed(node->right))
			return false;
		return true;
	}

	// ------------------------------------------------------------------ //

public:
	~Tree(){
		Node*now = root;
		while (now){
			if (now->left)
				now = now->left;
			else if (now->right)
				now = now->right;
			else{
				Node*next = now->parent;
				*get_parent_ptr(now) = 0;
				delete now;
				now = next;
			}
		}
	}

	Tree(const Tree&other){
		if (other.is_empty())
			root = 0;
		else{
			root = new Node(other.root->value);
			try{
				Node
					*now = root,
					*other_now = other.root;
				while (other_now){
					if (other_now->left && !now->left){
						now->left = new Node(other_now->left->value);
						now->left->parent = now;
						now = now->left;
						other_now = other_now->left;
					}
					else if (other_now->right && !now->right){
						now->right = new Node(other_now->right->value);
						now->right->parent = now;
						now = now->right;
						other_now = other_now->right;
					}
					else{
						now = now->parent;
						other_now = other_now->parent;
					}
					assert(is_wellformed(root));
				}
			}
			catch (...){
				this->~Tree();
				throw;
			}
		}
	}

public:
	void swap(Tree&other){
		std::swap(root, other.root);
	}

	Tree&operator=(const Tree&other){
		Tree temp(other);
		swap(temp);
		return *this;
	}

	// ------------------------------------------------------------------ //

private:
	template<class NodeT>
	static NodeT*search(NodeT*root, const T&value){
		NodeT*now = root;
		while (now){
			if (value < now->value)
				now = now->left;
			else if (now->value < value)
				now = now->right;
			else
				return now;
		}
		return 0;
	}

public:
	bool contains(const T&t)const{
		return search(root, t);
	}

	// ------------------------------------------------------------------ //

public:
	bool insert(const T&value){
		Node
			*parent = 0,
			*now = root;
		bool is_left_child = false;
		while (now){
			parent = now;
			if (value < now->value){
				is_left_child = true;
				now = now->left;
			}
			else if (now->value < value){
				is_left_child = false;
				now = now->right;
			}
			else
				return false; // Das Element ist bereits im Baum
		}
		Node*new_node = new Node(value);
		new_node->parent = parent;

		if (parent == 0)
			root = new_node;
		else if (is_left_child)
			parent->left = new_node;
		else
			parent->right = new_node;


		// Wenn etwas mit den Zeigern falsch ist,
		// dann knallt es wahrscheinlich hier.
		assert(is_wellformed(root));
		return true;
	}

	// ------------------------------------------------------------------ //

private:
	void swap_near_nodes(Node*child, Node*parent){
		// Als erstes passen wir den unbeteiligten Gro�elternknoten an.
		*get_parent_ptr(parent) = child;

		// Anschlie�end werden die Kind- und Elternzeiger ausgetauscht.
		std::swap(parent->left, child->left);
		std::swap(parent->right, child->right);
		std::swap(parent->parent, child->parent);

		// Da eines der Kinder getauscht wird, ben�tigt es eine
		// Sonderbehandlung.
		if (child->left == child)
			child->left = parent;
		else
			child->right = parent;

		// Nun sind alle Kindzeiger richtig und die Elternzeiger k�nnen
		// dem angepasst werden.
		if (child->left)
			child->left->parent = child;
		if (child->right)
			child->right->parent = child;
		if (parent->left)
			parent->left->parent = parent;
		if (parent->right)
			parent->right->parent = parent;

		// Na, wer ist sich noch sicher, ob wir nicht
		// bereits Zeigersalat haben? Besser testen!
		assert(is_wellformed(root));
	}

	void swap_far_nodes(Node*a, Node*b){
		// Zuerst updaten wir die Zeiger der Eltern
		*get_parent_ptr(a) = b;
		*get_parent_ptr(b) = a;

		// Danach der Kinder
		if (a->left)
			a->left->parent = b;
		if (a->right)
			a->right->parent = b;
		if (b->left)
			b->left->parent = a;
		if (b->right)
			b->right->parent = a;

		// Und als letztes die der beiden Knoten
		std::swap(a->left, b->left);
		std::swap(a->right, b->right);
		std::swap(a->parent, b->parent);

		assert(is_wellformed(root));
	}

	void swap_nodes(Node*a, Node*b){
		if (a->parent == b)
			swap_near_nodes(a, b);
		else if (b->parent == a)
			swap_near_nodes(b, a);
		else
			swap_far_nodes(a, b);
	}

	// ------------------------------------------------------------------ //

private:
	template<class NodeT>
	static NodeT*get_min(NodeT*node){
		NodeT*now = node;
		while (now->left)
			now = now->left;
		return now;
	}

	template<class NodeT>
	static NodeT*get_max(NodeT*node){
		NodeT*now = node;
		while (now->right)
			now = now->right;
		return now;
	}


public:
	const T&min()const{
		return get_min(root)->value;
	}

	const T&max()const{
		return get_max(root)->value;
	}

	// ------------------------------------------------------------------ //

private:
	template<class NodeT>
	static NodeT*get_next_node(NodeT*now){
		if (now->right)
			return get_min(now->right);
		else{
			while (now){
				if (is_left_child(now))
					return now->parent;
				else
					now = now->parent;
			}
			return 0; // Wir sind am Ende angekommen
		}
	}

	template<class NodeT>
	static NodeT*get_prev_node(NodeT*now){
		if (now->left)
			return get_max(now->left);
		else{
			while (now){
				if (is_right_child(now))
					return now->parent;
				else
					now = now->parent;
			}
			return 0; // Wir sind am Anfang angekommen
		}
	}

public:
	const T*next(const T&value)const{
		const Node*now = search(root, value);
		if (!now)
			return 0;
		now = get_next_node(now);
		if (now)
			return &now->value;
		else
			return 0;
	}

	const T*prev(const T&value)const{
		const Node*now = search(root, value);
		if (!now)
			return 0;
		now = get_prev_node(now);
		if (now)
			return &now->value;
		else
			return 0;
	}

	// ------------------------------------------------------------------ //

private:
	void remove(Node*node){
		// Ein Blatt
		if (!node->left && !node->right){
			*get_parent_ptr(node) = 0;
			delete node;
		}
		// Nur ein Kind
		else if (node->left && !node->right){
			*get_parent_ptr(node) = node->left;
			node->left->parent = node->parent;
			delete node;
		}
		else if (!node->left && node->right){
			*get_parent_ptr(node) = node->right;
			node->right->parent = node->parent;
			delete node;
		}
		// Zwei Kinder
		else{
			Node*other = get_prev_node(node);
			swap_nodes(node, other);
			// L�schen des Knotens durch Benutzen von einer
			// der beiden anderen Methoden
			remove(node);
		}
		assert(is_wellformed(root));
	}
public:
	bool remove(const T&value){
		Node*node = search(root, value);
		if (node){
			remove(node);
			return true;
		}
		else
			return false;
	}

	void print_head(const Tree<int>&t, ostream&out){
		if (t.is_empty())
			out << "The tree is empty." << endl;
		else
			t.dump(out);

		out << "\n";
	}

	Node *get_root() {
		return root;
	}

	void mirror_tree_topdown(Node *root) {
		// we swap children as long root is not NULL
		if (root) {
			std::swap(root->left, root->right);
		}

		if (!root) {
			return;
		}

		mirror_tree_topdown(root->left);
		mirror_tree_topdown(root->right);
	}

	void mirror_tree_bottomup(Node *root) {
		if (!root) {
			return;
		}

		mirror_tree_bottomup(root->left);
		mirror_tree_bottomup(root->right);

		// we swap children as long root is not NULL
		if (root) {
			std::swap(root->left, root->right);
		}
	}

	void get_depth_min_max(Node *root, int &min_depth, int &max_depth) {
		static int depth = 0;

		if (!root) {
			return;
		}

		if (!root->left || !root->right) {
			if (depth > max_depth) {
				max_depth = depth;
			}
			if (depth < min_depth) {
				min_depth = depth;
			}
		}

		depth++;

		get_depth_min_max(root->left, min_depth, max_depth);
		get_depth_min_max(root->right, min_depth, max_depth);

		depth--;
	}

	bool is_tree_ballanced(Node *root) {
		int min_depth = numeric_limits<int>::max();
		int max_depth = numeric_limits<int>::min();

		get_depth_min_max(root, min_depth, max_depth);

		return abs(min_depth - max_depth) <= 1;
	}

	vector<vector<int>> get_paths_with_sum(Node *root, int sum) {
		vector<vector<int>> paths_with_sum;
		vector<Node*> current_path;
		stack<Node*> s;
		int current_total_sum = 0;

		s.push(root);

		while (!s.empty()) {
			Node *current_node = s.top();
			s.pop();

			current_total_sum += current_node->value;
			current_path.push_back(current_node);

			// if the sum of the current value equals the sum we are looking for
			// we store the current path
			if (current_total_sum == sum && !current_node->left && !current_node->right) {
				vector<int> curr_path;

				for (auto it = current_path.begin(); it != current_path.end(); it++) {
					Node *tmp = *it;
					curr_path.push_back(tmp->value);
				}

				paths_with_sum.push_back(curr_path);
			}

			bool has_child = false;
			if (current_node->right) {
				s.push(current_node->right);
				has_child = true;
			}
			if (current_node->left) {
				s.push(current_node->left);
				has_child = true;
			}

			if (!has_child) {
				Node *curr = current_path.back();
				Node *prev = NULL;

				while (curr && !current_path.empty()) {
					if (prev == curr->left && curr->right) {
						break;
					}

					current_total_sum -= current_path.back()->value;

					prev = curr;

					current_path.pop_back();
					curr = current_path.back();
				}
			}
		}

		return paths_with_sum;
	}

	void get_paths_with_sum_recursive(Node *root, int sum, vector<vector<int>> &paths) {
		static int total_sum = 0;
		static vector<int> current_path;

		if (!root) {
			return;
		}

		total_sum += root->value;
		current_path.push_back(root->value);

		if (total_sum == sum && !root->left && !root->right) {
			paths.push_back(current_path);
		}

		get_paths_with_sum_recursive(root->left, sum, paths);
		get_paths_with_sum_recursive(root->right, sum, paths);

		total_sum -= root->value;

		current_path.pop_back();
	}
};

int main() {
	Tree<int> t4;
	t4.insert(10);
	t4.insert(5);
	t4.insert(12);
	t4.insert(4);
	t4.insert(3);
	t4.insert(2);
	t4.insert(7);
	t4.insert(14);
	
	t4.print_head(t4, cout);

	return 0;
}