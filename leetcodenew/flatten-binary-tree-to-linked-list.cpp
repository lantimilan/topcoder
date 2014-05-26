/**
 * flatten-binary-tree-to-linked-list.cpp
 * https://oj.leetcode.com/problems/flatten-binary-tree-to-linked-list/
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
    void flatten(TreeNode *root) {
        if (root == NULL) return;
        if (root->left == NULL && root->right == NULL) return;
        // what happens in subtree does not affect root
        flatten(root->left);
        flatten(root->right);
        TreeNode *right = root->right;
        root->right = root->left; root->left = NULL;
        TreeNode *tail = root;
        while (tail->right != NULL) tail = tail->right;
        tail->right = right;
    }
};
