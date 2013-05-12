// RBtree.cpp
//
// implements a Red-Black tree

#include <iostream>
using namespace std;

template<class T>
class RBTreeNode;

// RBTree class
template<class T>
class RBTree
{
private:
    void print(RBTreeNode<T> *node, int level);
    void dumprec(RBTreeNode<T> *node, int level);
public:
    RBTreeNode<T> *root;
    RBTree();
    RBTree(RBTreeNode<T> *node);
    void dump();
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
        cout << "  ";
    }
    cout << node->val << endl;
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

enum RBColor {
    RED,    // 0
    BLACK,  // 1
};

// RBTreeNode class
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
}
