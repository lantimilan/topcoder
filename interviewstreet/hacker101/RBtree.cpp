// RBtree.cpp
//
// implements a Red-Black tree

#include <iomanip>
#include <iostream>
using namespace std;

template<class T>
class RBTreeNode;

// RBTree class
template<class T>
class RBTree
{
private:
    static const int INDENT = 4;
    void print(RBTreeNode<T> *node, int level);
    void dumprec(RBTreeNode<T> *node, int level);
    RBTreeNode<T>* insert_rec(T val, RBTreeNode<T> *node);
public:
    RBTreeNode<T> *root;
    RBTree();
    RBTree(RBTreeNode<T> *node);
    void dump();

    RBTreeNode<T>* insert(T val);
};

template<class T>
RBTree<T>::RBTree()
{
    root = NULL;
}

template<class T>
RBTree<T>::RBTree(RBTreeNode<T> *node)
{
    root = node;
}

template<class T>
void RBTree<T>::print(RBTreeNode<T> *node, int level)
{
    for (int i = 0; i < level; ++i) {
        for (int k = 0; k < INDENT; ++k)
            cout << ' ';
    }
    cout << setw(4) << node->val << endl;
}

template<class T>
void RBTree<T>::dumprec(RBTreeNode<T> *node, int level)
{
    if (node == NULL) return;
    print(node, level);
    dumprec(node->left, level+1);
    dumprec(node->right, level+1);
}

template<class T>
void RBTree<T>::dump()
{
    cout << "dump:\n";
    dumprec(root, 0);
}

template<class T>
RBTreeNode<T>*
RBTree<T>::insert(T val)
{
    if (root == NULL) {
        return root = new RBTreeNode<T>(val);
    } else {
        return insert_rec(val, root);
    }
}

template<class T>
RBTreeNode<T>*
RBTree<T>::insert_rec(T val, RBTreeNode<T> *node)
{
    if (node->val < val) {
        if (node->right == NULL) {
            return node->right = new RBTreeNode<T>(val);
        } else {
            return insert_rec(val, node->right);
        }
    } else if (node->val > val) {
        if (node->left == NULL) {
            return node->left = new RBTreeNode<T>(val);
        } else {
            return insert_rec(val, node->left);
        }
    } else {
        // ignore if equal
    }
}

// RBTreeNode class
enum RBColor {
    RED,    // 0
    BLACK,  // 1
};

template<class T>
class RBTreeNode
{
private:
    T val;
    RBColor c;
    RBTreeNode *left, *right;

public:
    RBTreeNode();
    RBTreeNode(T val);
    RBTreeNode(T val, RBColor c, RBTreeNode *left, RBTreeNode *right);

    T get_val();

friend class RBTree<T>;
};

template<class T>
RBTreeNode<T>::RBTreeNode() : val(T())
{
    c = BLACK;
    left = right = NULL;
}

template<class T>
RBTreeNode<T>::RBTreeNode(T val2) : val(val2)
{
    c = BLACK;
    left = right = NULL;
}

template<class T>
RBTreeNode<T>::RBTreeNode(T val2, RBColor c2, RBTreeNode *left2, RBTreeNode *right2) : val(val2)
{
    c = c2;
    left = left2;
    right = right2;
}

template<class T>
T RBTreeNode<T>::get_val()
{
    return val;
}

// test program
int main()
{
    RBTreeNode<int> *node = new RBTreeNode<int>(10);
    RBTree<int> *rbtree = new RBTree<int>(node);
    rbtree->dump();
    cout << "--------------------------\n";

    cout << endl;
    cout << "insert 5\n";
    rbtree->insert(5);
    rbtree->dump();
    cout << "--------------------------\n";

    cout << endl;
    cout << "insert 15\n";
    rbtree->insert(15);
    rbtree->dump();
    cout << "--------------------------\n";

    cout << endl;
    cout << "insert 8\n";
    rbtree->insert(8);
    rbtree->dump();
    cout << "--------------------------\n";

    cout << endl;
    cout << "insert 4\n";
    rbtree->insert(4);
    rbtree->dump();
    cout << "--------------------------\n";
}
