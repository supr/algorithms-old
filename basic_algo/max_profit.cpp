/*
Question:
You have given Amazon's stock prices for next 10 days 
Find out: what is the best sell and buy time that makes max benefit in best time complexity.
buy and sell 1 share condition: Share must be sold any day after buying date. 

days:         0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
stock prices: 5   1   4   6   7   9   4   3   5   3   7   8
*/

#include <iostream>
#include <vector>
using namespace std;

int find_max_profit(vector<int> &vec) {
  int profit = 0;
  bool bought = false;
  int i = 0;
  
  for(i = 1; i < vec.size(); i++) {
    int delta = vec[i] - vec[i-1];
    
    if (delta > 0) {
      profit += delta;
      
      if (!bought) {
        cout << "buy at " << i - 1 << "th day" << endl;
        bought = true;
      }
    }
    else if (delta < 0) {
      if (bought) {
        cout << "sold at " << i - 1 << "th day" << endl;
        bought = false;
      }
    }
  }
  
  if (bought) {
    cout << "sold at day " << i - 1 << endl;
  }
  
  return profit;
}

int main() {
  // your code goes here
  
  vector<int> stocks = {5, 1, 4, 6, 7, 9, 4, 3, 5, 3, 7, 8};
  
  cout << find_max_profit(stocks) << endl;
  
  return 0;
}