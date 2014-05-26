/**
 * convert-sorted-array-to-binary-search-tree.cpp
 * https://oj.leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
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
    TreeNode *sortedArrayToBST(vector<int> &num) {
        if (num.empty()) return NULL;
        if (num.size() == 1) return new TreeNode(num[0]);
        vector<int> left, right;
        for (int i = 0; i < num.size()/2; ++i) left.push_back(num[i]);
        for (int i = num.size()/2 + 1; i < num.size(); ++i) right.push_back(num[i]);
        int root_val = num[num.size()/2];
        TreeNode *root = new TreeNode(root_val);
        TreeNode *lchild = sortedArrayToBST(left);
        TreeNode *rchild = sortedArrayToBST(right);
        root->left = lchild; root->right = rchild;
        return root;
    }
};
