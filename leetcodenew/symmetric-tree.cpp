/**
 * symmetric-tree.cpp
 * https://oj.leetcode.com/problems/symmetric-tree/
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
    bool isSymmetric(TreeNode *root) {
        if (root == NULL) return true;
        return isMirror(root->left, root->right);
    }

    bool isMirror(TreeNode *tree1, TreeNode *tree2) {
        if (tree1 == NULL && tree2 == NULL) return true;
        if (tree1 == NULL || tree2 == NULL) return false;
        // now both tree1 and tree2 are not NULL
        if (tree1->val != tree2->val) return false;
        return isMirror(tree1->left, tree2->right) &&
            isMirror(tree1->right, tree2->left);
    }
};
