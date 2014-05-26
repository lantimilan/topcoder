/**
 * binary-tree-level-order-traversal
 * https://oj.leetcode.com/problems/binary-tree-level-order-traversal/
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
    vector<vector<int> > levelOrder(TreeNode *root) {
        if (root == NULL) return vector<vector<int> >();
        map<TreeNode*, int> level_map;
        vector<TreeNode*> bfsvec;
        queue<TreeNode*> que; que.push(root); level_map[root] = 0; bfsvec.push_back(root);
        while (!que.empty()) {
            TreeNode *start = que.front(); que.pop();
            if (start->left) {
                TreeNode *left = start->left;
                que.push(left);
                level_map[left] = level_map[start] + 1;
                bfsvec.push_back(left);
            }
            if (start->right) {
                TreeNode *right = start->right;
                que.push(right);
                level_map[right] = level_map[start] + 1;
                bfsvec.push_back(right);
            }
        }

        vector<vector<int> > ans;
        int last = 0;
        vector<int> cur(1, bfsvec[0]->val);
        for (int i = 1; i < bfsvec.size(); ++i) {
            TreeNode *node = bfsvec[i];
            if (level_map[node] > last) {
                ans.push_back(cur);
                cur = vector<int>(1, node->val);
                last = level_map[node];
            } else if (level_map[node] == last) {
                cur.push_back(node->val);
            }
        }
        ans.push_back(cur);
        return ans;
    }
};
