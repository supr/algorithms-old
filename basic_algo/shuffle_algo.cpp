/*
Question:
Write a method to shuffle a deck of cards. It must be a perfect shuffle - in other words, 
each 52! permutations of the deck has to be equaliy likely. Assume that you are given a random 
number generator which is perfect.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void shuffle(vector<int> &vec) {
  for (int i = vec.size() - 1; i > 0; i--) {
    int r = rand() % i;

    swap(vec[i], vec[r]);
  }
}

int main() {
  vector<int> vec = {1, 2, 3, 4, 5, 6, 7};

  srand( time( NULL ) );
  shuffle(vec);

  for_each(vec.begin(), vec.end(), [](int val) { cout << val << ' '; });

  return 0;
}