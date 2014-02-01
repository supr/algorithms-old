#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
using namespace std;

/* Question:
Given an Array A = { -2, 4, 30, -50, 90, -60, 100, 120 }
The indices of the array indicate day numbers.
Say 0 - Monday, 1 - Thuesday....etc
And value represents stock price at that time.
You can only make one buy trade and one sell
* trade, and the buy must occur on a date before the sell.
* Print out the buy and sell day numbers that make the most money
* and the profit you would achieve.

Get the max profit.i.e in this input,
best buying price = -60
best selling price = 120

Solution: find_best_buy_price_stock1: O(n^2)
Solution: find_best_buy_price_stock2: O(n)
*/

int find_min_index(const vector<int> &dailyStockPrices, int start_index) {
	int min = numeric_limits<int>::max();
	int min_index = start_index;

	for (int i = start_index; i >= 0; i--) {
		if (dailyStockPrices[i] < min) {
			min = dailyStockPrices[i];
			min_index = i;
		}
	}

	return min_index;

}

void find_best_buy_price_stock1(const vector<int> &dailyStockPrices) {
	int max_profit = 0;
	int buy_index = 0;
	int sell_index = 0;
	int profit = 0;

	for (int i = 1; i < dailyStockPrices.size(); i++) {
		int current_buy_index = find_min_index(dailyStockPrices, i);

		profit = dailyStockPrices[i] - dailyStockPrices[current_buy_index];

		if (profit > max_profit) {
			buy_index = current_buy_index;
			sell_index = i;
			max_profit = profit;
		}
	}

	cout << "max_profit: " << max_profit << ", buy_date: " << buy_index << ", sell_date: " << sell_index << endl;
}

void find_best_buy_price_stock2(const vector<int> &dailyStockPrices) {
	if (dailyStockPrices.size() <= 1) {
		cout << "no proper profit possible" << endl;
	}

	int current_min = dailyStockPrices[0];
	int max_profit = 0;
	int buy_date = 0;
	int sell_date = 0;
	int buy_date_tmp = 0;

	for (int i = 1; i < dailyStockPrices.size(); i++) {
		if (dailyStockPrices[i] < current_min) {
			current_min = dailyStockPrices[i];
			buy_date_tmp = i;
			continue;
		}

		int profit = dailyStockPrices[i] - current_min;
		if (profit > max_profit) {
			max_profit = profit;
			sell_date = i;
			buy_date = buy_date_tmp;
		}
	}

	if (max_profit == 0) {
		cout << "no proper profit possible" << endl;
	}
	else {
		cout << "max_profit: " << max_profit << ", buy_date: " << buy_date << ", sell_date: " << sell_date << endl;
	}
}

int main() {
	vector<int> facebook = { 1, 2, 3, 4, 5 };
	find_best_buy_price_stock1(facebook);
	find_best_buy_price_stock2(facebook);

	vector<int> google = { 2, 3, 5, 7, 1 };
	find_best_buy_price_stock1(google);
	find_best_buy_price_stock2(google);

	vector<int> goldman = { 7, 4, 1, 5, 3 };
	find_best_buy_price_stock1(goldman);
	find_best_buy_price_stock2(goldman);

	return 0;
}