/**
 * binary-tree-preorder-traversal.cpp
 * https://oj.leetcode.com/problems/binary-tree-preorder-traversal/
 * 
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 * 
 * This solution uses a stack
 * there are three orders, inorder, preorder and postorder binary tree traversal
 * and correspondingly there are three states a node can be in:
 * 1. pre_time, when it is first discovered and gets pushed into stack
 * 2. in_time, when its left child is done, or NULL
 * 3. post_time, when both its children done, or NULL
 * 
 * we push a node into stack when it is first discovered
 * we pop a node out of stack when both its children done
 * we print a node (add to vector) when pre_time for preorder
 * in_time for inorder
 * post_time for postorder
 * 
 * to record the fact when a node is done, we use set<Node*> done
 * 
 * invariant: we never push NULL into statck
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        if (root == NULL) return vector<int>();
        set<TreeNode*> done;
        vector<int> seq;
        stack<TreeNode*> st; st.push(root); seq.push_back(root->val);
        while (!st.empty()) {
            TreeNode *start = st.top();
            if (!is_done(start->left, done)) {
                st.push(start->left); seq.push_back(start->left->val);
            } else if (!is_done(start->right, done)) {
                st.push(start->right); seq.push_back(start->right->val);
            } else  { // both left and right are done
                st.pop(); done.insert(start);
            }
        }
        return seq;
    }
    
    bool is_done(TreeNode *node, const set<TreeNode*> &done) {
        if (node == NULL || done.count(node)) return true;
        else return false;
    }
};
