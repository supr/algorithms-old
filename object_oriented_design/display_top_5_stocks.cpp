#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

/* Question: 
We maintain stock prices of various companies. A stream of stock updates are coming in the form of 
ticker and value pair(example YHOO, 36.00). This value needs to be updated. We have a module of GUI that 
always displays top 5 stock prices at any given point of time. How would you maintain these values in memory?

Implementation:
- does not handle duplicate stock names -> support possible with linked list + hash table
*/

typedef struct Stock {
	string name;
	int value;
	Stock(string name_, int value_): name(name_), value(value_) {}
}Stock;

typedef struct Comparison {
	bool operator()(const Stock &lhs, const Stock &rhs) {
		return lhs.value > rhs.value;
	}
}Comparison;

class StockTicker {
private:	
	unsigned int stocks_display_max;
	priority_queue<Stock, vector<Stock>, Comparison> stocks;
	
public:
	StockTicker(unsigned int display_max): stocks_display_max(display_max) {}

	void insert(string name, int value) {
		if(stocks.size() < stocks_display_max) {
			stocks.push(Stock(name, value));
		}
		else {
			if(stocks.top().value < value) {
				stocks.pop();
				stocks.push(Stock(name, value));
			}
		}
	}

	void display_top_stocks() {
		priority_queue<Stock, vector<Stock>, Comparison> stocks_tmp = stocks;

		cout << "\nTop Stocks..." << endl;
		
		while(!stocks_tmp.empty()) {
			Stock s = stocks_tmp.top();
			stocks_tmp.pop();

			cout << "stock_name: " << s.name << ", stock_value: " << s.value << endl;
		}
	}
};

int main() {
	StockTicker ticker(2);
		
	ticker.insert("Google", 13);
	ticker.insert("Yahoo", 10);
	ticker.insert("Goldman", 16);
	ticker.insert("Apple", 20);
	ticker.insert("VMware", 14);
	
	ticker.display_top_stocks();

	return 0;
}