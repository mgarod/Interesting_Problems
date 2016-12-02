/*
Given N and M find all stepping numbers in range N to M

The stepping number:

A number is called as a stepping number if the adjacent digits have a difference of 1.
e.g 123 is stepping number, but 358 is not a stepping number

Example:

N = 10, M = 20
all stepping numbers are 10 , 12 

Return the numbers in sorted order.
*/

#include <iostream>
#include <vector>
using namespace std;

bool isStepping(int n) {
    int digit = n%10;
    n /= 10;
    while (n > 0) {
        int next_digit = n % 10;
        if (abs(digit - next_digit) != 1)
            return false;
        digit = next_digit;
        n /= 10;
    }
    return true;
}

vector<int> stepnum(int A, int B) {
    vector<int> answer;
    for (int i = A; i <= B; ++i) {
        if (isStepping(i))
            answer.push_back(i);
    }
    return answer;
}

void printVector(const vector<int>& v) {
  cout << "[";
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << "]" << endl;
}

int main() {

    vector<int> return_vector = stepnum(1000, 10000);
    printVector(return_vector);

    return 0;
}