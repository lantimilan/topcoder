/**
 * construct-binary-tree-from-inorder-and-postorder-traversal.cpp
 * https://oj.leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        int n = inorder.size();
        TreeNode *rootnode = helper(inorder, postorder, 0, n, 0, n);
        return rootnode;
    }

    TreeNode *helper(const vector<int> &inorder, const vector<int> &postorder, int x1, int x2, int y1, int y2) {
        if (x1 >= x2) return NULL;
        int root = postorder[y2-1];
        int split;
        for (split = x1; inorder[split] != root; ++split)
            ;
        TreeNode *rootnode = new TreeNode(root);
        int n1 = split - x1, n2 = x2 - x1 - n1;
        TreeNode *leftnode = helper(inorder, postorder, x1, split, y1, y1 + n1);
        TreeNode *rightnode = helper(inorder, postorder, split+1, x2, y1 + n1, y2 - 1);
        rootnode->left = leftnode;
        rootnode->right = rightnode;
        return rootnode;
    }
};
