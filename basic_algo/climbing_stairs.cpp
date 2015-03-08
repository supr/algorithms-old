#include <vector>
using namespace std;

/*
Question:
You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways 
can you climb to the top?
Notes: Fibonaci.
*/

class Solution {
public:
    int climbStairs(int n) {
        vector<int> N(n + 1);
        N[0] = 1;
        N[1] = 1;
        for (int i = 2; i <= n; ++i) {
            N[i] = N[i - 1] + N[i - 2];
        }
        return N.back();
    }
};

int main() {
  Solution s;
  cout << s.climbStairs(3) << endl;

  return 0;
}