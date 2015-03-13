#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Given a number N, represent N as a sum of non consequtive fibonacci numbers.
Fib seq: 1 2 3 5 8 13 21 34

N < 10^8

Examples:

INPUT IS N

Input: 11
Output: 3,8

Input 12
Output 8,3,1
*/

unsigned long fibonacci_iterative(int n) {
  unsigned long zero = 0;
  unsigned long first = 1;
  unsigned long num = 0;

  if (n <= 1) {
    return n;
  }

  for (int i = 2; i <= n; i++) {
    num = zero + first;
    zero = first;
    first = num;
  }

  return num;
}

vector<unsigned long> generate_fib_lut(int len) {
  vector<unsigned long> fib;
  
  for (int i = 0; i < len; i++) {
    fib.push_back(fibonacci_iterative(i));
  }
  
  return fib;
}

void print(const vector<unsigned long> &vec) {
  for (auto & e: vec) {
    cout << e << ' ';
  }
  cout << '\n';
}

auto find_next_smaller(const vector<unsigned long> &vec, const int key) { 
    auto it = std::lower_bound(vec.begin(), vec.end(), key); 
    if (it == vec.end()) { 
      it = (vec.rbegin()+1).base();
    }
    else if (it != vec.begin() && *it > key) { 
        --it; 
    }
    
    return it; 
} 

vector<unsigned long> find_non_cos_fib_seq(unsigned long N) {
  vector<unsigned long> fib_lut = generate_fib_lut(40);
  vector<unsigned long> seq;
  
  while (N) {
    auto it = find_next_smaller(fib_lut, N);
    seq.push_back(*it);
    N -= *it;
  }
  
  return seq;
}

int main() {
  // your code goes here
  
  vector<unsigned long> seq1 = find_non_cos_fib_seq(11);
  print(seq1);

  vector<unsigned long> seq2 = find_non_cos_fib_seq(12);
  print(seq2);
  
  return 0;
}