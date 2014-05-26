/**
 * convert-sorted-list-to-binary-search-tree.cpp
 * https://oj.leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
 *
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
        if (head == NULL) return NULL;
        if (head->next == NULL) return new TreeNode(head->val);

        ListNode *slow, *fast;
        for (slow = head, fast = head->next; fast != NULL && fast->next != NULL; ) {
            fast = fast->next->next;
            if (fast == NULL) break;
            slow = slow->next;  // for n = 2k, slow stops at k-1, for n = 2k+1, slow stops at k-1, 0-base position
        }
        int root_val = slow->next->val;
        TreeNode *root = new TreeNode(root_val);
        ListNode *left = head, *right = slow->next->next;
        slow->next = NULL;
        TreeNode *lchild = sortedListToBST(left);
        TreeNode *rchild = sortedListToBST(right);
        root->left = lchild; root->right = rchild;
        return root;
    }
};
