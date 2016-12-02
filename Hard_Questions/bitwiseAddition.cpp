/*
Implement a function that computes addition of numbers, without using mathematical operations such as operator+, or inequality operators.
*/

#include <iostream>
using namespace std;

int add(int a, int b) {
  int abit, bbit, rbit, result = 0 , carry = 0;

  for (int i = 31; i > 0; --i) {
    abit = a & 1;
    bbit = b & 1;
    rbit = (abit ^ bbit) ^ carry;
    result = (result >> 1 | rbit << 30);
    
    if ((abit && bbit) || ((abit ^ bbit) && carry))
      carry = 1;
    else
      carry = 0;

    a >>= 1;
    b >>= 1;
  }

  return result;
}

int main() {
  
  cout << add(12, 17) << endl;
  cout << add(3, 4) << endl;
  cout << add(301, 404) << endl;
}
