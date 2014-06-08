/**
 * merge-two-sorted-lists.cpp
 * https://oj.leetcode.com/problems/merge-two-sorted-lists/
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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *head, *tail;
        head = tail = NULL;
        for (; l1 || l2; ) {
            ListNode *cur;
            if (l1 == NULL || l2 == NULL) {
                cur = l1 ? l1 : l2;
                if (tail == NULL) {
                    head = tail = cur;
                } else {
                    tail->next = cur;
                }
                break;
            } else {  // both l1 and l2 are not NULL
                if (l1->val <= l2->val) {
                    cur = l1; l1 = l1->next;
                } else {
                    cur = l2; l2 = l2->next;
                }
                if (tail == NULL) {
                    head = tail = cur; tail->next = NULL;
                } else {
                    tail->next = cur; tail = tail->next; tail->next = NULL;
                }
            }
        }
        return head;
    }

};
