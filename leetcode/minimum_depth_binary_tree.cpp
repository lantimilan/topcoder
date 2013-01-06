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
    int minDepth(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) return 0;
        int d1, d2;
        d1 = minDepth(root->left);
        d2 = minDepth(root->right);
        
        if (d1 == 0 || d2 == 0) return 1 + max(d1, d2);
        else return 1 + min(d1, d2);    
    }
};