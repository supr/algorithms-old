#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cassert>
#include <deque>
using namespace std;

// Basic Tree implementation --------------------------------------------------------------------------------------------------------------------------------------------------------- //
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

    // Der hoechste Unterbaum bestimmt die Gesamthoehe
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
      // In beiden Unterbaeumen sind die Wurzeln um eins niedriger und darum veraendert
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

public:
  ~Tree(){
    /*Node*now = root;
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
    }*/
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

private:
  void swap_near_nodes(Node*child, Node*parent){
    // Als erstes passen wir den unbeteiligten Grosselternknoten an.
    *get_parent_ptr(parent) = child;

    // Anschliessend werden die Kind- und Elternzeiger ausgetauscht.
    std::swap(parent->left, child->left);
    std::swap(parent->right, child->right);
    std::swap(parent->parent, child->parent);

    // Da eines der Kinder getauscht wird, benoetigt es eine
    // Sonderbehandlung.
    if (child->left == child)
      child->left = parent;
    else
      child->right = parent;

    // Nun sind alle Kindzeiger richtig und die Elternzeiger koennen
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
      // Loeschen des Knotens durch Benutzen von einer
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

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------/

  void delete_all_nodes();
  void delete_all_nodes_internal(Node *root);
  Node* BST_to_doubly_linked_list();
  Node* BST_to_doubly_linked_list_internal(Node *curr, Node **prev);
  Node* get_parent(Node *curr, Node *to_find);
  Node* get_most_left_node(Node *curr);
  void delete_node(Node *curr);
  Node* find_k_max_node(Node *root, int k);
  void find_k_max_node_internal(Node *root, int &counter, int &k, Node **n); 
  Node* lca(Node *root, Node *p, Node *q, deque<Node*> &path, bool &both_found);
  void dfs(Node *root, bool &found, Node *find, deque<Node*> &path);
  deque<Node*> path_between_p_q(Node *root, Node *p, Node *q);
  Node* get_next_node_depthfirst(Node *curr);
  Node* get_next_node_inorder(Node *current);
  Node* get_next_node_inorder2(Node *curr);
  Node* get_next_node_inorder2_internal(Node *root, Node *curr);
  Node* get_next_node_postorder(Node *root, Node *curr);
  Node* find_next_node(Node *root);
  bool is_leaf(Node *root);
  Node* get_next_node_postorder2(Node *root, Node *curr);
  Node* postorder_successor(Node *curr);
  Node* postorderSuccessor_internal2(Node *root, Node *curr, Node *direct_parent, Node *parent, Node *treeroot);
  Node* get_next_node_preorder(Node *current);
  Node* get_next_node_preorder2(Node *curr);
  Node* get_next_node_preorder2_internal(Node *root, Node *curr);
  void inorder_traversal_recursive(Node *root);
  void inorder_traversal_iterative(Node *root);
  bool is_tree_balanced1(Node *root);
  bool dfs(Node *root, int &curr_depth, int &min_depth, int &max_depth);
  int get_max_depth(Node *root);
  int get_min_depth(Node *root);
  bool is_tree_balanced2(Node *root);
  Node* in_order_iterator(Node *root);
  Node* get_most_right_node(Node *root);
  Node* in_order_iterator_mirrored(Node *root);
  bool is_tree_symmetrical(Node *root);
  bool is_mirror_tree_recursive(Node *LP, Node *RP);
  bool is_mirror_tree_iterative(Node *root);
  vector<vector<int>> level_order_traversal(Node *root);
  Node* lowest_common_ancestor(Node *root, Node *n1, Node *n2);
  int max_depth(Node *root);
  int max_depth2(Node *root);
  int min_depth1(Node *root);
  int min_depth2(Node *root);
  void mirror_tree_topdown(Node *root);
  void mirror_tree_bottomup(Node *root);
  void print_all_paths_with_sum_iterative(Node *root, const int sum);
  void print_current_path(vector<int> &vec);
  void print_all_paths_with_sum_recursive(Node *root, const int sum);
  void print_all_paths_with_sum_util(Node *root, vector<int> &curr_path, int &curr_sum, const int sum);
  void postorder_traversal_recursive(Node *root);
  void postorder_traversal_iterative(Node *root);
  void postorder_traversal_iterative2(Node *root);
  void preorder_traversal_recursive(Node *root);
  void preorder_traversal_iterative(Node *root);
  void print_all_paths(Node *root, vector<int> &vec);
  void print_paths_from_root(Node *root);
  void print_paths_from_root_util(Node *root, vector<Node*> &s);
  void recover_binary_tree_internal(Node *root, Node **prev, Node **first_node_not_inorder);
  void recover_binary_tree(Node *root);
  void trim_BST(Node *curr, int min, int max);
  Node* trim_BST_internal(Node *root, int min, int max);
  bool is_BST_internal1(Tree<T>::Node *root, int min, int max);
  bool is_BST1();
  bool is_BST_internal2(Tree<T>::Node *root, int &prev_value);
  bool is_BST2();


};