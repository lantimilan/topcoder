// BinaryTreeSerialization.cpp
//
// to serialize and deserialize a binary tree
// ebay initiali onsite technical screening
// The solution I had during the interview is level by level
// and each node serialize to a string "key:hasLeft:hasRight"
// example: a node with key=5 and has left child but not right child
// is encoded as "5:1:0"
// serialize is done via BFS using a queue, level order traversal
// deserialize is done using two passes, first pass construct nodes
// with lchild = rchild = NULL
// second pass will hook child pointer to the correct child
//
// Here is a better solution, using DFS
// recursion invariant:
// * serialize:
// for each node we have "key:B/L/R/N" for both, lchild, rchild and NULL
// notice that we need to know whether a node has left or right child
// as it will be ambiguous otherwise
// * deserialize
// Node* constuct(const vector<string> &tokens, int &start)
// this will construct a subtree starting at tokens[start]
// and move start to the appropriate postition for next node

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node *left, *right;

    Node(int x) {
        val = x;
        left = right = NULL;
    }
};

string encode(Node *node) {
    int val = node->val;
    char ch;
    if (node->left && node->right) ch = 'B';  // both children
    else if (node->left) ch = 'L';  // lchild
    else if (node->right) ch = 'R';  // rchild
    else ch = 'N';  // null
    ostringstream oss; oss << val;
    string token = oss.str() + ":" + ch;
    return token;
}

void serialHelper(Node *root, vector<string> &tokens) {
    if (root == NULL) return;
    string s = encode(root);
    tokens.push_back(s);
    serialHelper(root->left, tokens);
    serialHelper(root->right, tokens);
}

vector<string> serialize(Node *root) {
    vector<string> tokens;
    serialHelper(root, tokens);
    return tokens;
}

int getChild(string token) {
    switch (token[token.size()-1]) {
        case 'N': return 0;
        case 'L': return 1;
        case 'R': return 2;
        case 'B': return 3;
    }
}

Node* deserialHelper(const vector<string> &tokens, int &start) {
    if (start >= tokens.size()) return NULL;
    string token = tokens[start];
    string strval = token.substr(0, token.length() - 2);  // subtract ":L"
    int child = getChild(token); // 0 NULL, 1 LEFT, 2 RIGHT, 3 BOTH

    int val;
    istringstream iss(strval); iss >> val;
    Node *cur = new Node(val);
    if (child & 1) {
        Node *lchild = deserialHelper(tokens, ++start);
        cur->left = lchild;
    }
    if (child & 2) {
        Node *rchild = deserialHelper(tokens, ++start);
        cur->right = rchild;
    }
    return cur;
}

Node* deserialize(const vector<string> &tokens) {
    int start = 0;
    return deserialHelper(tokens, start);
}

bool isEqual(Node *tree1, Node *tree2) {
    if (tree1 == NULL && tree2 == NULL) return true;
    if (tree1 == NULL || tree2 == NULL) return false;
    if (tree1->val != tree2->val) return false;
    return isEqual(tree1->left, tree2->left) &&
        isEqual(tree1->right, tree2->right);
}

int main()
{
    Node *root = new Node(5);
    Node *l1 = new Node(3); root->left = l1;
    Node *r1 = new Node(10); root->right = r1;
    Node *l2 = new Node(1); l1->left = l2;
    Node *r2 = new Node(15); r1->right = r2;

    vector<string> tokens = serialize(root);
    cout << "tokens: ";
    for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens[i] << "  ";
    } cout << endl;
    Node *newroot = deserialize(tokens);
    assert(isEqual(root, newroot));
}

// careful, if you do not return, then you got segmentation fault
//
// TODO: wrap everything into a BinaryTree class

