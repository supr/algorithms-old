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
using namespace std;

/*
Question: Convert a BST to a sorted circular doubly-linked list in-place. 
Think of the left and right pointers as synonymous to the previous and next pointers in a doubly-linked list.

The algorithm is implemented in two different ways:
- Node *BST_to_doubly_linked_list()
*/

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


Node* BST_to_doubly_linked_list() {
  Node *prev = NULL;
  BST_to_doubly_linked_list_internal(root, &prev);

  return root;
}

void BST_to_doubly_linked_list_internal(Node *curr, Node **prev) {
  if (!curr) {
    return;
  }

  BST_to_doubly_linked_list_internal(curr->left, prev);

  if (!(*prev)) {
    *prev = curr;
    root = curr;
  } else {
    (*prev)->right = curr;
    curr->left = *prev;
    *prev = curr;
  }

  BST_to_doubly_linked_list_internal(curr->right, prev);
}
};

int main() {
  Tree<int> t;
  t.insert(10);
  t.insert(5);
  t.insert(12);
  t.insert(4);
  t.insert(7);

  t.print_head(t, cout);
  
  Tree<int>::Node *prev = NULL;
  Tree<int>::Node *curr = t.BST_to_doubly_linked_list();

  while(curr) {
    cout << curr->value << ' ';
    prev = curr;
    curr = curr->right; 
  }

 cout << '\n' << endl;
  
  while(prev) {
    cout << prev->value << ' ';
    prev = prev->left; 
  }
  
  return 0;
}