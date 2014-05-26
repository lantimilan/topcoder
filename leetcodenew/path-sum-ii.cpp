/**
 * path-sum-ii.cpp
 * https://oj.leetcode.com/problems/path-sum-ii/
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
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int> > ans = helper(root, sum);
        for (int i = 0; i < ans.size(); ++i) reverse(ans[i].begin(), ans[i].end());
        return ans;
    }
    vector<vector<int> > helper(TreeNode *root, int sum) {
        vector<vector<int> > ans;
        if (root == NULL) return ans;
        if (root->left == NULL && root->right == NULL) {
            if (root->val == sum) {
                ans.push_back(vector<int>(1, sum));
                return ans;
            } else {
                return ans;
            }
        }
        vector<vector<int> > left = helper(root->left, sum - root->val);
        vector<vector<int> > right = helper(root->right, sum - root->val);
        for (int i = 0; i < left.size(); ++i) { left[i].push_back(root->val); ans.push_back(left[i]); }
        for (int i = 0; i < right.size(); ++i) { right[i].push_back(root->val); ans.push_back(right[i]); }
        return ans;
    }
};
