// BinaryTreeLCA.cpp

#include <iostream>
#include <set>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        left = right = NULL;
    }
};

bool is_done(TreeNode *node, const set<TreeNode*> &doneset) {
    return node == NULL || doneset.count(node);
}

stack<TreeNode*> search(TreeNode *root, int val) {
    stack<TreeNode*> st; st.push(root);
    set<TreeNode*> doneset;
    while (!st.empty()) {
        TreeNode *top = st.top();
        if (top->val == val) return st;
        if (!is_done(top->left, doneset)) st.push(top->left);
        else if (!is_done(top->right, doneset)) st.push(top->right);
        else { st.pop(); doneset.insert(top); }
    }
    return st;
}

void print(stack<TreeNode*> st)
{
    cout << "print stack: ";
    while (!st.empty()) {
        int v = st.top()->val; cout << ' ' << v;
        st.pop();
    }
    cout << endl;
}

int LCA(TreeNode *root, int v1, int v2) {
    stack<TreeNode*> st1 = search(root, v1); print(st1);
    stack<TreeNode*> st2 = search(root, v2); print(st2);
    while (st1.size() > st2.size()) st1.pop();
    while (st2.size() > st1.size()) st2.pop();
    while (st1.top()->val != st2.top()->val) st1.pop(), st2.pop();
    return st1.top()->val;
}

int main()
{
    TreeNode *d10= new TreeNode(10);
    TreeNode *d1 = new TreeNode(1);
    TreeNode *d5 = new TreeNode(5);
    TreeNode *d20 = new TreeNode(20);
    TreeNode *d30 = new TreeNode(30);
    TreeNode *d7 = new TreeNode(7);
    TreeNode *d13 = new TreeNode(13);
    TreeNode *d18 = new TreeNode(18);

    d10->left = d5; d10->right = d20;
    d5->left = d1; d5->right = d7;
    d20->left = d18; d20->right = d30;
    d18->left = d13;

    TreeNode *root = d10;
    int val;
    int v1 = 5, v2 = 20;
    val = LCA(root, v1, v2);
    cout << "LCA of " << v1 << " and " << v2 << ": " << val << endl;

    v1 = 13; v2 = 30;
    val = LCA(root, v1, v2);
    cout << "LCA of " << v1 << " and " << v2 << ": " << val << endl;

    v1 = 20; v2 = 13;
    val = LCA(root, v1, v2);
    cout << "LCA of " << v1 << " and " << v2 << ": " << val << endl;
}
