/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 *
 * use a stack of Node, this allows us to do a DFS like traversal
 * Node is printed once left subtree is done
 *
 * several catches
 * we need to remember whethere a node has printed or not
 * otherwise we have no idea when return from rchild
 * also need to check both left and right for done, as right child
 * might be done simply because it is NULL
 *
 * 1. we never push NULL into stack
 * 2. the nodes get in and out of stack following DFS
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        set<TreeNode*> done;
        set<TreeNode*> printed;
        stack<TreeNode*> st;
        if (root == NULL) return vector<int>();
        vector<int> inorderList;
        st.push(root);
        while (!st.empty()) {
            TreeNode *start = st.top();
            if (is_done(start->left, done) && !printed.count(start)) {
                inorderList.push_back(start->val); printed.insert(start);
                if (!is_done(start->right, done)) st.push(start->right);
            }
            if (is_done(start->left, done) && is_done(start->right, done)) {
                done.insert(start); st.pop();
            }
            if (!is_done(start->left, done)) {
                st.push(start->left);
            }
        }
        return inorderList;
    }



    bool is_done(TreeNode *node, const set<TreeNode*> &done) {
        return node == NULL || done.count(node);
    }
};
