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
class hashtable
{
private:
	string *key_arr;
	unsigned int *value_arr;
	int *status_arr; // contains the status of the table at index pos: deleted, empty or used
	unsigned int size;

private:
	unsigned int hash(string key)
	{
		int sum = 0;
		
		for(unsigned int i = 0; i < key.size(); i++)
		{
			sum = sum + static_cast<unsigned int>(key[i]);
		}

		sum = sum % size;
		
		return sum;
	}

public:
	hashtable(int n): size(n)
	{
		value_arr = new unsigned int[n];
		status_arr = new int[n];
		key_arr = new string[n];

		for(unsigned int i = 0; i < n; i++)
		{
			status_arr[i] = 0;
		}
	}

	void add(const string &key, const unsigned int &value)
	{
		unsigned int hash_index = hash(key);
		unsigned int j = 0;

		if(status_arr[hash_index] != 1)
		{
			key_arr[hash_index] = key;
			value_arr[hash_index] = value;
			status_arr[hash_index] = 1;
		}
		else
		{
			do {
				hash_index ++;
				hash_index = hash_index % size;

				if(status_arr[hash_index] != 1)
				{
					key_arr[hash_index] = key;
					value_arr[hash_index] = value;
					status_arr[hash_index] = 1;

					return;
				}
				else
				{
					j++;
				}
			} while(j < size);

			throw("Error collision");
		}
	}

	bool contains(const string &key)
	{
		unsigned int hash_index = hash(key);
		int j = 0;

		do
		{
			if(status_arr[hash_index] == 1 && key == key_arr[hash_index])
			{
				return true;
			}
			else if(status_arr[hash_index] == 0)
			{
				return false;
			}
			else
			{
				j++;
			}

			hash_index ++;
			hash_index = hash_index % size;
		}while(j < size);

		return false;
	}

	unsigned int item(const string &key)
	{
		unsigned int hash_index = hash(key);
		int j = 0;

		do
		{
			if(status_arr[hash_index] == 1 && key == key_arr[hash_index])
			{
				return value_arr[hash_index];
			}
			else if(status_arr[hash_index] == 0)
			{
				throw("Error calling item");
			}
			else
			{
				j++;
			}

			hash_index ++;
			hash_index = hash_index % size;
		}while(j < size);

		throw("Error calling item");
	}

	bool remove(const string &key)
	{
		unsigned int hash_index = hash(key);
		int j = 0;

		do
		{
			if(status_arr[hash_index] == 1 && key == key_arr[hash_index])
			{
				value_arr[hash_index] = 0;
				status_arr[hash_index] = -1;

				return true;
			}
			else if(status_arr[hash_index] == 0)
			{
				return false;
			}
			else
			{
				j++;
			}

			hash_index ++;
			hash_index = hash_index % size;
		}while(j < size);

		return false;
	}

	~hashtable()
	{
		delete[] value_arr;
		delete[] key_arr;
		delete[] status_arr;
	}
};



