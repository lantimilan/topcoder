/**
 * binary-tree-level-order-traversal-ii.cpp
 * https://oj.leetcode.com/problems/binary-tree-level-order-traversal-ii/
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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        if (root == NULL) return vector<vector<int> >();
        queue<TreeNode*> que1, que2;
        map<TreeNode*, int> dist_map;
        que1.push(root); que2.push(root);
        dist_map[root] = 0;
        while (!que1.empty()) {
            TreeNode *start = que1.front(); que1.pop();
            if (start->left) {
                TreeNode *left = start->left;
                dist_map[left] = dist_map[start] + 1;
                que1.push(left); que2.push(left);
            }
            if (start->right) {
                TreeNode *right = start->right;
                dist_map[right] = dist_map[start] + 1;
                que1.push(right); que2.push(right);
            }
        }
        int dist = -1;
        vector<vector<int> > ans;
        while (!que2.empty()) {
            TreeNode *cur = que2.front(); que2.pop();
            int d = dist_map[cur];
            if (d != dist) {
                vector<int> vec(1, cur->val);
                ans.push_back(vec);
                dist = d;
            } else {
                ans[d].push_back(cur->val);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
