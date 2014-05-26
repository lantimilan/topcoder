/**
 * maximum-depth-of-binary-tree.cpp
 * https://oj.leetcode.com/problems/maximum-depth-of-binary-tree/
 *
 * it is convenient to extend definition of depth to NULL, which has depth = 0
 * this gives leaf at depth=1 and other non-leaf nodes still have the same depth
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
    int maxDepth(TreeNode *root) {
        if (root == NULL) return 0;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return 1 + max(left, right);
    }
};
