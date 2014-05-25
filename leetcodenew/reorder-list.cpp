// reorder-list.cpp
// https://oj.leetcode.com/problems/reorder-list/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode *head) {
        // is there a way to do without count number of nodes?
        int n = 0;
        for (ListNode *p = head; p != NULL; p = p->next) ++n;
        if (n <= 2) return;

        int mid = (n-1) / 2;  // if n is 2k, stop at k-1, if n is 2k+1, stop at k
        ListNode *left = head, *right;
        for (int i = 0; i < mid; ++i) left = left->next;
        right = left->next; left->next = NULL;
        right = reverse(right);
        ListNode *p = head, *q = right;
        ListNode *newhead, *tail;
        newhead = tail = p; p = p->next;
        tail->next = q; q = q->next;
        tail = tail->next;
        for (; q != NULL; ) {
            ListNode *p1, *q1;
            p1 = p->next; q1 = q->next;
            tail->next = p; tail = tail->next;
            tail->next = q; tail = tail->next;
            p = p1; q = q1;
        }
        if (p != NULL) tail->next = p;
        // return newhead;  // no need to return head, as head is already in correct position and never changes
    }
    ListNode* reverse(ListNode *head) {
        ListNode *newhead = NULL;
        ListNode *p, *q;
        for (p = head; p != NULL; p = q) {
            q = p->next;
            p->next = newhead; newhead = p;
        }
        return newhead;
    }
};
