/**
 * construct-binary-tree-from-preorder-and-inorder-traversal.cpp
 * https://oj.leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        int n = preorder.size();
        return helper(preorder, inorder, 0, n, 0, n);
    }
    TreeNode *helper(const vector<int> &preorder, const vector<int> &inorder, int x1, int x2, int y1, int y2) {
        if (x1 >= x2) return NULL;
        int root = preorder[x1];
        int split;
        for (split = y1; inorder[split] != root; ++split)
            ;
        int n1 = split - y1;
        int n2 = y2 - y1 - n1 - 1;
        TreeNode *leftnode = helper(preorder, inorder, x1+1, x1+1+n1, y1, split);
        TreeNode *rightnode = helper(preorder, inorder, x1+1+n1, x2, split+1, y2);
        TreeNode *rootnode = new TreeNode(root);
        rootnode->left = leftnode;
        rootnode->right = rightnode;
        return rootnode;
    }
};
