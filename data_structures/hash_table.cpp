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
   Search: O(n) ... n is the size of the hashtable
   Remove: O(n)
*/

#include <iostream>
#include <string>
using namespace std;

class Hashtable {
private:
  int size;
  string *keyArr;
  int *valueArr;
  int *statusArr; // contains the status of the table at index pos: deleted (-1), empty (0) or used (1)
  
private:
  int calculate_hash(string key) {
    int sum = 0;
    
    for(int i = 0; i < key.size(); i++) {
      sum = sum + static_cast<unsigned int>(key[i]);
    }
    
    return sum % size;
  }
  
public:
  Hashtable(int size_): size(size_) {
    keyArr = new string[size];
    valueArr = new int[size];
    statusArr = new int[size];
    
    for(int i = 0; i < size; i++) {
      statusArr[i] = 0;
    }
  }
  
  bool insert(const string key, int value) {
    int hash = calculate_hash(key);
    int i = 0;
    int index = 0;
    
    while(i < size) {
      index = (hash + i) % size;

      if(statusArr[index] != 1) {
        keyArr[index] = key;
        valueArr[index] = value;
        statusArr[index] = 1;
        return true;
      }
      else if(keyArr[index] == key) {
        valueArr[index] = value;
        return true;
      }
      
      i++;
    }
    
    return false;
  }
  
  int find(const string &key) {
    int hash = calculate_hash(key); 
    int i = 0;
    int index = 0;
    
    while(i < size) {
      index = (hash + i) % size;
      
      if(statusArr[index] == 1 && keyArr[index] == key) {
        return valueArr[index];
      }
      else if(statusArr[index] == 0) {
        return -1;
      }
      
      i++;
    }
    
    return -1;
  }
  
  bool erase(const string &key) {
    int hash = calculate_hash(key); 
    int i = 0;
    int index = 0;
    
    while(i < size) {
      index = (hash + i) % size;
      
      if(statusArr[index] == 1 && keyArr[index] == key) {
        valueArr[index] = 0;
        statusArr[index] = -1;
        return true;
      }
      else if(statusArr[index] == 0) {
        return false;
      }
      
      i++;
    }
    
    return false;
  }

  ~Hashtable() {
    delete[] value_arr;
    delete[] key_arr;
    delete[] status_arr;
  }
};
 
int main() {
  Hashtable ht(10);
  ht.insert("k1", 1);
  ht.insert("k2", 2);
  ht.insert("k1", 5);
 
  cout << "k1: " << ht.find("k1") << endl;
  cout << "k2: " << ht.find("k2") << endl;
  cout << "k3: " << ht.find("k3") << endl;
 
  ht.erase("k2");
  cout << "k2: " << ht.find("k2") << endl;
 
  return 0;
}
