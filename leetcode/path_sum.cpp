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
    bool hasPathSum(TreeNode *root, int sum) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL) return false;
        if (root->left == NULL &&
            root->right == NULL &&
            root->val == sum) {
            return true;
        }
        bool b1, b2;
        b1 = hasPathSum(root->left, sum - root->val);
        b2 = hasPathSum(root->right, sum - root->val);
        return b1 || b2;
    }
};
