// Hashtable
/* A hash table stores objects in a table. It is a data structure that uses a hash 
   function to map identifying values, known as keys (e.g., a person's name), to their 
   associated values (e.g., their telephone number). 
   The hash function is used to transform the key into the index (the hash) of an array  
   element.
   Ideally, the hash function should map each possible key to a unique slot index, but   
   this ideal is rarely achievable in practice.
   A good hash function is required (e.g.: operation % prime number) to ensure that the    
   hash values are uniformly distributed.

   Open hashing ... using a list for elements having the same hash value
   Closed hashing ... use the next entry in the array if you more than one hash value

   Insert: O(1)
   Search: O(1) ... if elements have the same hash value: O(n) ... n is the size of the hashtable
   Remove: O(1) ... if elements have the same hash value: O(n) ... n is the size of the hashtable

   Reference: http://www.algolist.net/Data_structures/Hash_table/Simple_example
              http://blog.aozturk.me/simple-hash-map-hash-table-implementation-in-c
*/

#include <iostream>
using namespace std;

const long TABLE_SIZE = 128;

// Hash node class template
template <typename K, typename V>
class HashNode {
public:
    HashNode(const K &key, const V &value): key(key), value(value) {}

    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    void setValue(V value) {
        value = value;
    }

private:
    // key-value pair
    K key;
    V value;
};

// Hash map class template
template <typename K, typename V>
class HashMap {
public:
    HashMap() {
        // construct zero initialized hash table of size
        table = new HashNode<K, V> *[TABLE_SIZE]();
        for (int i = 0; i < TABLE_SIZE; i++) {
          table[i] = NULL; 
        }
    }

    ~HashMap() {
        // destroy all buckets one by one
        for (int i = 0; i < TABLE_SIZE; i++) {
          delete table[i]; 
        }
        // destroy the hash table
        delete[] table; 
    }

    bool get(const K &key, V &value) {
        unsigned long hash = hashFunc(key);
        
        while (table[hash] != NULL && table[hash]->getKey() != key) {
          hash = (hash + 1) % TABLE_SIZE; 
        }
        
        if (table[hash] == NULL) {
          return false;
        }
        
        value = table[hash]->getValue();
        return true;
    }

    void put(const K &key, const V &value) {
        unsigned long hash = hashFunc(key);
        
        while (table[hash] != NULL && table[hash]->getKey() != key) {
          hash = (hash + 1) % TABLE_SIZE;
        }
        
        if (table[hash] != NULL) {
          delete table[hash]; 
        }
        
        table[hash] = new HashNode<K, V>(key, value);   
    }

    void remove(const K &key) {
        unsigned long hash = hashFunc(key);

        while (table[hash] != NULL && table[hash]->getKey() != key) {
          hash = (hash + 1) % TABLE_SIZE; 
        }
        
        // key not found
        if (table[hash] == NULL) {
          return;
        }
        
        delete table[hash];
        table[hash] = NULL;
    }

private:
    // hash table
    HashNode<K, V> **table;
    
private:
    unsigned long hashFunc(const K &key) const {
      return static_cast<unsigned long>(key) % TABLE_SIZE;
    }
};

int main() {
  // your code goes here
  
  HashMap<int, string> hmap;
  hmap.put(1, "val1");
  hmap.put(2, "val2");
  hmap.put(3, "val3");
  
  string value;
  hmap.get(2, value);
  cout << value << endl;
  bool res = hmap.get(3, value);
  if (res) {
      cout << value << endl;
  }
  hmap.remove(3);
  res = hmap.get(3, value);
  if (res) {
      cout << value << endl;
  }
  
  return 0;
}