/**
 * remove-duplicates-from-sorted-list.cpp
 * https://oj.leetcode.com/problems/remove-duplicates-from-sorted-list/
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
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode *newhead, *tail, *p, *next;
        newhead = tail = NULL;
        for (p = head; p != NULL; p = next) {
            next = p->next;
            if (tail == NULL) {
                newhead = tail = p; tail->next = NULL;
            } else {
                if (tail->val == p->val) {}
                else {
                    tail->next = p; tail = tail->next;
                    tail->next = NULL;
                }
            }
        }
        return newhead;
    }
};
