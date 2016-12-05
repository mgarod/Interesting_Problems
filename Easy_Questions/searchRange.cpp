/*
https://codelab.interviewbit.com/problems/searchrange/

Given a sorted array of integers, find the starting and ending position of a given target value.
Your algorithm’s runtime complexity must be in the order of O(log n).
If the target is not found in the array, return [-1, -1].

Example: Given [5, 7, 7, 8, 8, 10] and target value 8, return [3, 4].
*/

vector<int> searchRange(const vector<int> &A, int B) {
    int low_index = -1;
    int hi = A.size()-1, lo = 0;
    while (hi >= lo) {
        int mid = lo + ((hi - lo) / 2);
        if (A[mid] == B) {
            low_index = mid;
            hi = mid - 1;
        } else if (A[mid] < B) { // search right
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    int high_index = -1;
    hi = A.size()-1, lo = 0;
    while (hi >= lo) {
        int mid = lo + ((hi - lo) / 2);
        if (A[mid] == B) {
            high_index = mid;
            lo = mid + 1;
        } else if (A[mid] < B) { // search right
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    return {low_index, high_index};
}
