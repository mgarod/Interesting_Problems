/*
https://codelab.interviewbit.com/problems/pascal1/

Given numRows (A), generate the first numRows of Pascal’s triangle.
*/

vector<vector<int>> Solution::generate(int A) {
    vector<vector<int>> answer;
    if (A >= 1)
        answer.push_back({1});
    if (A >= 2)
        answer.push_back({1,1});
    for (int i = 3; i <= A; ++i) {
        vector<int> row(i, 0);
        row[0] = answer.back()[0];
        for (int j = 1; j < i-1; ++j) {
            row[j] = answer.back()[j-1] + answer.back()[j];
        }
        row.back() = answer.back().back();
        answer.push_back(row);
    }
    return answer;
}
