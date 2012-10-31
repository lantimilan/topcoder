/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
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
    TreeNode *sortedListToBST(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == NULL) return NULL;
        TreeNode *root;
        if (head->next == NULL) {
            root = new TreeNode(head->val);
            return root;
        }
        // list has at least 2 nodes
        ListNode *p1, *p2, *prev;
        for(p1=p2=head; p2 && p2->next; p1=p1->next, p2=p2->next->next) {
            prev = p1;
        }
        root = new TreeNode(prev->next->val);
        TreeNode *left, *right;
        ListNode *h2 = prev->next->next;
        prev->next = NULL;
        left = sortedListToBST(head);
        right = sortedListToBST(h2);
        // delete prev->next ?
        root->left = left;
        root->right = right;
        return root;
    }
};