/**
 * recover-binary-search-tree.cpp
 * https://oj.leetcode.com/problems/recover-binary-search-tree/
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
    void recoverTree(TreeNode *root) {
        // 1. we know root is not NULL because it has at least two nodes

        if (root == NULL) return;
        if (root->left == NULL && root->right == NULL) return;

        // at least one of left and right subtree is not null
        if (root->left == NULL) {
            pair<TreeNode*, TreeNode*> p = getRange(root->right);
            if (root->val > p.first->val) {
                swap(root->val, p.first->val);
                return;
            } else {
                recoverTree(root->right);
                return;
            }
        }
        if (root->right == NULL) {
            pair<TreeNode*, TreeNode*> p = getRange(root->left);
            if (root->val < p.second->val) {
                swap(root->val, p.second->val);
                return;
            } else {
                recoverTree(root->left);
                return;
            }
        }

        // now both left and right subtree not null
        pair<TreeNode*, TreeNode*> p1 = getRange(root->left);
        pair<TreeNode*, TreeNode*> p2 = getRange(root->right);
        // if swap is between left and right subtree, then max_in_left > root > min_in_right
        // and we swap max_in_left with min_in_right
        if (p1.second->val > root->val && root->val > p2.first->val) {
            swap(p1.second->val, p2.first->val); return;
        }
        // if swap is between root and left subtree, then min_in_right > max_in_left > root
        // and we swap max_in_left with root
        if (p2.first->val > p1.second->val && p1.second->val > root->val) {
            swap(p1.second->val, root->val); return;
        }
        // if swap is between root and right subtree, then root > min_in_right > max_in_left
        // and we swap min_in_right with root
        if (root->val > p2.first->val && p2.first->val > p1.second->val) {
            swap(p2.first->val, root->val); return;
        }
        // if swap is within left subtree, or within right subtree, recurse
        if (!isBST(root->left)) recoverTree(root->left);
        else recoverTree(root->right);
    }

    void chmin(TreeNode * &t1, TreeNode *t2) {
        if (t1->val > t2->val) t1 = t2;
    }
    void chmax(TreeNode * &t1, TreeNode *t2) {
        if (t1->val < t2->val) t1 = t2;
    }

    pair<TreeNode*,TreeNode*> getRange(TreeNode *root) {
        if (root->left == NULL && root->right == NULL) return make_pair(root, root);
        TreeNode *minNode, *maxNode;
        minNode = maxNode = root;
        if (root->left) {
            pair<TreeNode*,TreeNode*> p = getRange(root->left);
            chmin(minNode, p.first);
            chmax(maxNode, p.second);
        }
        if (root->right) {
            pair<TreeNode*, TreeNode*> p = getRange(root->right);
            chmin(minNode, p.first);
            chmax(maxNode, p.second);
        }
        return make_pair(minNode, maxNode);
    }

    bool isBST(TreeNode *root) {
        if (root == NULL) return true;
        if (root->left == NULL && root->right == NULL) return true;
        if (root->left) {
            pair<TreeNode*,TreeNode*> p = getRange(root->left);
            if (!isBST(root->left)) return false;
            if (p.second->val > root->val) return false;
        }
        if (root->right) {
            pair<TreeNode*, TreeNode*> p = getRange(root->right);
            if (!isBST(root->right)) return false;
            if (root->val > p.first->val) return false;
        }
        return true;
    }
};
