/**
 * binary-tree-maximum-path-sum.cpp
 * https://oj.leetcode.com/problems/binary-tree-maximum-path-sum/
 *
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 *
 * dp[node] is the max sum following a path from node to a leaf of its subtree
 * ans = max(eval(node)) for all nodes
 *
 */
class Solution {
public:
    map<TreeNode*, int> dp;

    int maxPathSum(TreeNode *root) {
        if (root == NULL) return 0;
        dp.clear();
        recurse(root);
        int ans = eval(root);
        return ans;
    }

    int recurse(TreeNode *root) {
        if (dp.count(root)) return dp[root];
        if (root == NULL) return dp[root] = 0;
        dp[root] = 0;
        int left = recurse(root->left);
        int right = recurse(root->right);
        int ans = root->val + max(left, right);
        if (ans > 0) dp[root] = ans;
        return dp[root];
    }

    int eval(TreeNode *node) {
        if (node == NULL) return 0;
        int cur = dp[node->left] + dp[node->right] + node->val;
        int left = eval(node->left);
        int right = eval(node->right);
        if (node->left != NULL) cur = max(cur, left);
        if (node->right != NULL) cur = max(cur, right);
        return cur;
    }
};
