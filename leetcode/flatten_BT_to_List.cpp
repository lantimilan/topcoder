/**
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
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) return;
        TreeNode *left, *right;
        left = root->left;
        right = root->right;
        root->left = root->right = NULL;
        flatten(left);
        flatten(right);
        
        TreeNode *p = root;
        
        while (left) {
            p->right = left;
            p = p->right;
            left = left->right;
        }
        while (right) {
            p->right = right;
            p = p->right;
            right = right->right;
        }
    }
};