/*
https://codelab.interviewbit.com/problems/remduplnk/

Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <unordered_set>
ListNode* Solution::deleteDuplicates(ListNode* A) {
    if (A == nullptr || A->next == nullptr) {
        return A;
    }
    unordered_set<int> set;
    ListNode* prev = A;
    set.insert(prev->val);
    ListNode* curr = A->next;
    while (curr != nullptr) {
        if (set.count(curr->val)) {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } else {
            set.insert(curr->val);
            prev = curr;
            curr = curr->next;
        }
    }
    return A;
}

