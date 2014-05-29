/**
 * validate-binary-search-tree.cpp
 * https://oj.leetcode.com/problems/validate-binary-search-tree/
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
    bool isValidBST(TreeNode *root) {
        if (root == NULL) return true;
        int minval, maxval;
        return checkBST(root, minval, maxval);
    }

    bool checkBST(TreeNode *root, int &minval, int &maxval) {
        if (root->left == NULL && root->right == NULL) {
            minval = maxval = root->val;
            return true;
        }
        minval = maxval = root->val;
        if (root->left) {
            int minleft, maxleft;
            if (checkBST(root->left, minleft, maxleft)) {
                minval = minleft;
                if (maxleft >= root->val) return false;
            } else return false;
        }
        if (root->right) {
            int minright, maxright;
            if (checkBST(root->right, minright, maxright)) {
                maxval = maxright;
                if (root->val >= minright) return false;
            } else return false;
        }
        return true;
    }
};
