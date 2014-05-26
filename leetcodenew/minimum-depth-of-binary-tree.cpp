/**
 * minimum-depth-of-binary-tree.cpp
 * https://oj.leetcode.com/problems/minimum-depth-of-binary-tree/
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
    int minDepth(TreeNode *root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return 1;  // at leaf

        int left = -1, right = -1;
        if (root->left) left = minDepth(root->left);
        if (root->right) right = minDepth(root->right);
        int depth = -1;
        if (left >= 0) depth = left;
        if (right >= 0) {
            if (depth < 0 || depth > right) depth = right;
        }
        return 1 + depth;
    }
};
