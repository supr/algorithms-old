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


class Hashtable {
private:
	string *key_arr;
	unsigned int *value_arr;
	int *status_arr; // contains the status of the table at index pos: deleted, empty or used
	unsigned int size;

private:
	unsigned int hash(string key) {
		int sum = 0;

		for(unsigned int i = 0; i < key.size(); i++) {
			sum = sum + static_cast<unsigned int>(key[i]);
		}

		sum = sum % size;

		return sum;
	}

public:
	Hashtable(int n): size(n) {
		value_arr = new unsigned int[n];
		status_arr = new int[n];
		key_arr = new string[n];

		for(unsigned int i = 0; i < n; i++) {
			status_arr[i] = 0;
		}
	}

	void insert(const string &key, const unsigned int &value) {
		unsigned int hash_index = hash(key);
		unsigned int offset = 0;
		unsigned int index = 0;

		while (offset < size) {
    			index = (hash_index + offset) % size_max;

			if(status_arr[hash_index] != 1) {
 				key_arr[hash_index] = key;
				value_arr[hash_index] = value;
				status_arr[hash_index] = 1;

				return;
			}
 			
			offset++;
  		}

		throw("Error calling insert");
	}

	unsigned int find(const string &key) {
		unsigned int hash_index = hash(key);
		unsigned int offset = 0;
		unsigned int index = 0;

		while (offset < size) {
    			index = (hash_index + offset) % size_max;

			if(status_arr[index] == 1 && key == key_arr[index]) {
 				return value_arr[index];
			}
 			else if(status_arr[index] == 0) {
				throw("Error calling find");
			}

			offset++;
  		}

		throw("Error calling find");
	}

	bool erase(const string &key) {
		unsigned int hash_index = hash(key);
		unsigned int offset = 0;
		unsigned int index = 0;

		while (offset < size) {
    			index = (hash_index + offset) % size_max;

			if(status_arr[index] == 1 && key == key_arr[index]) {
 				value_arr[index] = 0;
				status_arr[index] = -1;

				return true;
			}
 			else if(status_arr[index] == 0) {
				return false;
			}

			offset++;
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
  Hashtable map;
  map.insert("k1", 1);
  map.insert("k2", 2);
 
  map.insert("k1", 5);
 
  cout << "k2: " << map.find("k2") << endl;
  cout << "k3: " << map.find("k3") << endl;
 
  cout << "k2: " << map.remove("k2") << endl;
 
  return 0;
}
