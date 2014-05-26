/**
 * sum-root-to-leaf-numbers.cpp
 * https://oj.leetcode.com/problems/sum-root-to-leaf-numbers
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
    int sumNumbers(TreeNode *root) {
        vector<vector<int> > numbers = helper(root);
        int ans = 0;
        for (int i = 0; i < numbers.size(); ++i) {
            int cur = 0;
            for (int j = numbers[i].size() - 1; j >= 0; --j)
                cur = cur * 10 + numbers[i][j];
            ans += cur;
        }
        return ans;
    }

    vector<vector<int> > helper(TreeNode *root) {
        if (root == NULL) return vector<vector<int> >();
        if (root->left == NULL && root->right == NULL)
            return vector<vector<int> >(1, vector<int>(1, root->val));
        vector<vector<int> > left = helper(root->left);
        vector<vector<int> > right = helper(root->right);
        vector<vector<int> > ans;
        for (int i = 0; i < left.size(); ++i) {
            left[i].push_back(root->val); ans.push_back(left[i]);
        }
        for (int i = 0; i < right.size(); ++i) {
            right[i].push_back(root->val); ans.push_back(right[i]);
        }
        return ans;
    }
};
