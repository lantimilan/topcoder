/**
 * balanced-binary-tree.cpp
 * https://oj.leetcode.com/problems/balanced-binary-tree/
 *
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode *root) {
        pair<bool,int> p = helper(root);
        return p.first;
    }
    pair<bool,int> helper(TreeNode *root) {  // (isbal, depth)
        if (root == NULL) return make_pair(true, 0);
        int left, right;
        {  // left subtree
            pair<bool,int> p = helper(root->left);
            if (!p.first) return make_pair(false, 0);
            left = p.second;
        }
        {  // right subtree
            pair<int,int> p = helper(root->right);
            if (!p.first) return make_pair(false, 0);
            right = p.second;
        }
        if (abs(left - right) > 1) return make_pair(false, 0);
        return make_pair(true, 1 + max(left, right));
    }
};
