/**
 * reverse-linked-list-ii.cpp
 * https://oj.leetcode.com/problems/reverse-linked-list-ii/
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
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if (head == NULL) return NULL;
        // strategy
        // fix tail at node[m] (1-based)
        // starting at node[m] (1-based), keep detaching next and insert after node[m-1]
        // repeat n-m times
        // then attach the rest to tail
        if (m == 1) {
            ListNode *tail, *other;
            tail = head; other = tail->next; tail->next = NULL;
            for (int k = m+1; k <= n; ++k) {
                ListNode *cur = other; other = other->next;
                cur->next = head; head = cur;
            }
            tail->next = other;
        } else {
            ListNode *newhead = head, *tail, *other;
            for (int k = 1; k < m-1; ++k) newhead = newhead->next;
            tail = newhead->next;
            other = tail->next; tail->next = NULL;
            for (int k = m+1; k <= n; ++k) {
                ListNode *cur = other; other = other->next;
                cur->next = newhead->next; newhead->next = cur;
            }
            tail->next = other;
        }
        return head;
    }
};
