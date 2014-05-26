/**
 * binary-tree-zigzag-level-order-traversal.cpp
 * https://oj.leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        if (root == NULL) return vector<vector<int> >();

        queue<TreeNode*> que;
        map<TreeNode*, int> level_map;
        vector<TreeNode*> bfsvec;
        que.push(root); level_map[root] = 0; bfsvec.push_back(root);
        while (!que.empty()) {
            TreeNode *start = que.front(); que.pop();
            TreeNode *left = start->left;
            TreeNode *right = start->right;
            if (left) {
                que.push(left); level_map[left] = level_map[start] + 1;
                bfsvec.push_back(left);
            }
            if (right) {
                que.push(right); level_map[right] = level_map[start] + 1;
                bfsvec.push_back(right);
            }
        }
        vector<vector<int> > ans;
        vector<int> row; row.push_back(root->val);
        int last = level_map[bfsvec[0]];
        for (int i = 1; i < bfsvec.size(); ++i) {
            TreeNode *node = bfsvec[i];
            int level = level_map[node];
            if (level > last) {
                if (last & 1) reverse(row.begin(), row.end());
                ans.push_back(row);
                row = vector<int>(1, node->val);
                last = level;
            } else {
                // level == last
                row.push_back(node->val);
            }
        }
        if (last & 1) reverse(row.begin(), row.end());
        ans.push_back(row);

        return ans;
    }
};
