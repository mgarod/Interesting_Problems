/*
Given an array of integers, sort the array into a wave like array and return
it. In other words, arrange the elements into a sequence such that:
a1 >= a2 <= a3 >= a4 <= a5.....

Given [1, 2, 3, 4]

One possible answer : [2, 1, 4, 3]
Another possible answer : [4, 1, 3, 2]

NOTE : If there are multiple answers possible, return the one
thats lexicographically smallest.
So, in the example case, you will return [2, 1, 4, 3]
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> wave(vector<int> &A) {
    if (A.size() < 2)
        return A;
        
    sort(A.begin(), A.end());
    for (int i=0; i < A.size()-1; i+=2) {
        std::swap(A[i], A[i+1]);
    }

    return A;
}

void printVector(const vector<int>& v) {
  cout << "[";
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << "]" << endl;
}

int main() {
  vector<int> v1 = {1,2,3,4};
  wave(v1);
  printVector(v1);

  vector<int> v2 = {9,2,3,7,5,6,8,4};
  wave(v2);
  printVector(v2);

}
