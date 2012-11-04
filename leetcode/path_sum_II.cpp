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
    void dfs(TreeNode *root, int sum, vector<int> &pre, vector<vector<int> > &cum) {
        if (root == NULL) return;
        if (root->left == NULL && root->right == NULL && root->val == sum) {
            pre.push_back(root->val);
            cum.push_back(pre);
            pre.pop_back();
            return;
        }
        pre.push_back(root->val);
        dfs(root->left, sum - root->val, pre, cum);
        dfs(root->right, sum - root->val, pre, cum);
        pre.pop_back();
    }
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > ans;
        vector<int> pre;
        dfs(root, sum, pre, ans);
        return ans;
    }
};

// Accepted on first try
