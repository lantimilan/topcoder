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
    bool balance(TreeNode *root, int &depth) {
        if (root == NULL) {
            depth = 0;
            return true;
        }
        int d1, d2;
        bool b1, b2;
        b1 = balance(root->left, d1);
        b2 = balance(root->right, d2);
        depth = 1 + max(d1, d2);        
        if (b1 && b2 && abs(d1-d2) <= 1) return true;
        return false;
    }
    
    bool isBalanced(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int depth;
        return balance(root, depth);
    }
};