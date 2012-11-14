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
    bool isSameTree(TreeNode *p, TreeNode *q) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (!p || !q) return !p && !q;  // if one of them is NULL, both have to be NULL
        
        if (p->val != q->val) return false;
        
        bool b1, b2;
        b1 = isSameTree(p->left, q->left);
        b2 = isSameTree(p->right, q->right);
        
        return b1 && b2;        
    }
};