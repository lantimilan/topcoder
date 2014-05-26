/**
 * populating-next-right-pointers-in-each-node-ii.cpp
 * https://oj.leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
 *
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 *
 * next pointer is established by parent
 * one inner link and one inter link
 * recurse on its children
 * THE ABOVE ALGORITHM IS WRONG. because we sometimes need to trace back more than one layer
 * to find next pointer
 *
 * example:
 *            A
 *        B        C
 *      D   E         F
 *    G                 H
 * it is not possible to deduce we have G->next to H, given only knowledge of DEF layer
 * because G only knows its parent, D->next is E, but it would not know that E->next to F
 *
 * A layer by layer breadth-first search would obviously work for this problem
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL) return;
        map<TreeLinkNode*, int> dist_map;
        dist_map[root] = 0;
        queue<TreeLinkNode*> que, que2; que.push(root); que2.push(root);
        while (!que.empty()) {
            TreeLinkNode *start = que.front(); que.pop();
            TreeLinkNode *left = start->left;
            TreeLinkNode *right = start->right;
            if (left != NULL) {
                dist_map[left] = dist_map[start] + 1;
                que.push(left); que2.push(left);
            }
            if (right != NULL) {
                dist_map[right] = dist_map[start] + 1;
                que.push(right); que2.push(right);
            }
        }
        TreeLinkNode *first = que2.front(); que2.pop();
        while (!que2.empty()) {
            TreeLinkNode *cur = que2.front(); que2.pop();
            if (dist_map[first] == dist_map[cur]) {
                first->next = cur;
            }
            first = cur;
        }
    }
};
