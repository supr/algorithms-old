#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
Question: Add binary

Given two binary strings, return their sum (also a binary string).
For example,
a = "11"
b = "1"
Return "100".
*/

string add_binary(string in1, string in2) {
	string out;
	int diff = abs(in1.size() - in2.size());

	if (in1.size() > in2.size()) {
		for (int i = 0; i < diff; i++) {
			in2 = '0' + in2;
		}
	}
	else if (in2.size() > in1.size()) {
		for (int i = 0; i < diff; i++) {
			in1 = '0' + in1;
		}
	}

	char digit;
	char carry = '0';

	for (int i = in1.size() - 1; i >= 0; i--) {
		if (carry == '0') {
			if (in1[i] == '1' && in2[i] == '1') {
				carry = '1';
				digit = '0';
			}
			else if (in1[i] == '0' && in2[i] == '0') {
				carry = '0';
				digit = '0';
			}
			else {
				carry = '0';
				digit = '1';
			}
		}
		else {
			if (in1[i] == '1' && in2[i] == '1') {
				carry = '1';
				digit = '1';
			}
			else if (in1[i] == '0' && in2[i] == '0') {
				carry = '0';
				digit = '1';
			}
			else {
				carry = '1';
				digit = '0';
			}
		}

		out = digit + out;
	}

	if (carry == '1') {
		out = carry + out;
	}
	return out;
}

string zeroPadding(string s, int bits) {
  for (int i = 0; i < bits; i++) {
    s = "0" + s;
  } 
  
  return s;
}

class SumCarry {
public:
  char sum;
  char carry;
  SumCarry(char sum_, char carry_): sum(sum_), carry(carry_) {}
};

string addBinary(string a, string b) {
  int len1 = a.size();
  int len2 = b.size();
  string result('0', max(len1,len2)+1); // allocate one more carry bit
  char carry = '0';
  char sum = '0';                     // a=0,b=0         // a=0,b=1
  vector<vector<SumCarry>> andVec = {{SumCarry('0','0'), SumCarry('1','0')},
                                      // a=1,b=0         // a=1,b=1
                                     {SumCarry('1','0'), SumCarry('0','1')}};
  // addVector for carry=1                     // a=0,b=0         // a=0,b=1
  vector<vector<SumCarry>> andVecWithCarry = {{SumCarry('1','0'), SumCarry('1=0','1')},
                                               // a=1,b=0         // a=1,b=1
                                              {SumCarry('0','1'), SumCarry('1','1')}};  
  if (len1 < len2) {
    a = zeroPadding(a, len2 - len1);
  } else if (len1 > len2) {
    b = zeroPadding(b, len1 - len2);
  }
  
  for (int i = a.size() - 1; i >= 0; i--) {
    int indexX = a[i] - '0';
    int indexY = b[i] - '0';
    
    if (carry == '0') {
      auto p = andVec[indexX][indexY];
      sum = p.sum;
      carry = p.carry;
    } else if (carry == '1') {
      auto p = andVecWithCarry[indexX][indexY];
      sum = p.sum;
      carry = p.carry;
    }
    
    result[i+1] = sum;
  }
  
  if (carry == '1') {
    result[0] = carry;
  } else {
    result.erase(result.begin(), result.begin()+1);
  }
  
  return result;
}

int main() {
	// your code goes here

	cout << add_binary("11", "1") << endl;

  cout << addBinary("1100", "111") << endl;

  cout << addBinary("1", "1") << endl;

	return 0;
}