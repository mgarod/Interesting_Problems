/**
Given a Binary Tree, return a vector of vectors, where the i'th subvector
represents the i'th level of the tree. Let the first level be represented
left to right, and second represented right to left, the third left to right
and so on.


 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <queue>
#include <algorithm>
vector<vector<int> > Solution::zigzagLevelOrder(TreeNode* A) {
    vector<vector<int>> answer;
    queue<TreeNode*> q;
    bool l_to_r = false;
    if (A != nullptr) {
        q.push(A);
        answer.push_back({A->val});
    }
        
    while(!q.empty()) {
        vector<int> level;
        for (int i = q.size(); i > 0; --i) {
            TreeNode* n = q.front();
            q.pop();
            if (n->left != nullptr) {
                level.push_back(n->left->val);
                q.push(n->left);
            }
            if (n->right != nullptr) {
                level.push_back(n->right->val);
                q.push(n->right);
            }
        }
        if (!l_to_r)
            std::reverse(level.begin(), level.end());
        if (!level.empty())
            answer.push_back(level);
        l_to_r = !l_to_r;
    }
    return answer;
}



















