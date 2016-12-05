/*
https://codelab.interviewbit.com/problems/diagonal/

Given a N*N square matrix, return an array of its anti-diagonals.

Example:  
Input:  

1 2 3
4 5 6
7 8 9

Return the following :

[ 
  [1],
  [2, 4],
  [3, 5, 7],
  [6, 8],
  [9]
]


Input : 
1 2
3 4

Return the following  : 

[
  [1],
  [2, 3],
  [4]
]
*/
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> antiDiagonals(vector<vector<int> > &A) {
    vector<vector<int>> answer(A.size()*2-1);
    // Copy top row to lower left corner (upper left triangle)
    int j;
    for (j = 0; j < A[0].size(); ++j) {
        int i = 0;
        int jcopy = j;
        while (jcopy >= 0 && i < A.size()) {
            answer[j].push_back(A[i][jcopy]);
            ++i;
            --jcopy;
        }
    }
    // copy the remaining bottom right triangle
    int answer_row = j;
    for (int i = 1; i < A.size(); ++i) {
        int j = A[i].size()-1;
        int icopy = i;
        while (j >=0 && icopy < A.size()) {
            answer[answer_row].push_back(A[icopy][j]);
            ++icopy;
            --j;
        }
        ++answer_row;
    }
    
    return answer;
}

void printVector(const vector<vector<int>>& v) {
  cout << "[" << endl;
  for (int i = 0; i < v.size(); ++i) {
    cout << "  [";
    for (int j = 0; j < v[i].size(); ++j) {
      cout << v[i][j] << " ";
    }
    cout << "]," << endl;
  }
  cout << "]" << endl;
}

int main() {
  vector<vector<int>> matrix = {{1,2,3}, {4,5,6}, {7,8,9}};
  vector<vector<int>> anti_diagonals = antiDiagonals(matrix);
  printVector(anti_diagonals);
}