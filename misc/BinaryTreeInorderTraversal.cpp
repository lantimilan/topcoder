#include <iostream>
#include <stack>
#include <set>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        left = right = NULL;
    }
};

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

int main()
{
    TreeNode *root = new TreeNode(10);
    TreeNode *d1 = new TreeNode(5);
    //TreeNode *d2 = new TreeNode(20);
    root->left = d1; //root->right = d2;

    Solution sol;
    vector<int> inorder = sol.inorderTraversal(root);
    for (int i = 0; i < inorder.size(); ++i) {
        cout << inorder[i] << ' ';
    }
    cout << endl;
}
