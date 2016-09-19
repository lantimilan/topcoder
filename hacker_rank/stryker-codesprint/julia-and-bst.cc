// julia-and-bst.cc
#include <iostream>
using namespace std;

struct Node {
    Node *left, *right;
    int val;
    Node(int val) {
        this->val = val;
        left = right = nullptr;
    }
};

long long sum = 0;

void insert(Node *root, Node *child) {
    if (root == nullptr) {
        root = child;
    } else {
        if (root->val > child->val) {
            if (root->left == nullptr) {
                root->left = child;
            } else {
                insert(root->left, child);
            }
        } else {
            if (root->right == nullptr) {
                root->right = child;
            } else {
                insert(root->right, child);
            }
        }
    }
}

void traverse(Node *root, int depth) {
    if (root == nullptr) return;
    sum += depth;
    traverse(root->left, depth+1);
    traverse(root->right, depth+1);
}

int main() {
    int n; cin >> n;
    Node *root = nullptr;
    for (int i = 0; i < n; ++i) {
        int val; cin >> val;
        Node *node = new Node(val);
        insert(root, node);
        if (root == nullptr) {
            root = node;
        }
    }
    traverse(root, 0);
    cout << sum << endl;

}

