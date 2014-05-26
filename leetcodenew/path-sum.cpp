/**
 * path-sum.cpp
 * https://oj.leetcode.com/problems/path-sum/
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
    bool hasPathSum(TreeNode *root, int sum) {
        if (root == NULL) return false; //sum == 0; this depends on the interpretation of whether a NULL tree has path sum zero
        if (root->left == NULL && root->right == NULL)
            return root->val == sum;
        int target = sum - root->val;
        return hasPathSum(root->left, target) ||
            hasPathSum(root->right, target);
    }
};
