/**
 * binary-tree-postorder-traversal
 * https://oj.leetcode.com/problems/binary-tree-postorder-traversal/
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
    vector<int> postorderTraversal(TreeNode *root) {
        if (root == NULL) return vector<int>();
        set<TreeNode*> done;
        vector<int> seq;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode *start = st.top();
            if (!is_done(start->left, done)) {
                st.push(start->left);
            } else if (!is_done(start->right, done)) {
                st.push(start->right);
            } else {
                // both children done
                seq.push_back(start->val);
                st.pop();
                done.insert(start);
            }
        }
        return seq;
    }
    
    bool is_done(TreeNode *node, const set<TreeNode*> &done) {
        return node == NULL || done.count(node);
    }
};
