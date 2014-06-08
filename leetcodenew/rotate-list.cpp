/**
 * rotate-list.cpp
 * https://oj.leetcode.com/problems/rotate-list/
 *
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        int len = 0;
        ListNode *p, *q;
        for (p = head; p != NULL; p = p->next, ++len) ;
        if (len == 0) return head;
        k %= len;
        if (k == 0) return head;
        p = q = head;
        for (int i = 0; i < k; ++i) q = q->next;
        for (; q->next != NULL; p = p->next, q = q->next) ;
        ListNode *newhead = p->next; p->next = NULL;
        for (p = newhead; p->next != NULL; p = p->next) ;
        p->next = head;
        return newhead;
    }
};
