/**
 * remove-duplicates-from-sorted-list-ii.cpp
 * https://oj.leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
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
        ListNode *newhead, *tail;
        ListNode *p;
        ListNode *start, *end;

        newhead = tail = NULL;
        for (p = head; p != NULL; p = end) {
            start = p; end = p->next;
            while (end != NULL && end->val == start->val) end = end->next;

            // end is either NULL or first element after start with a different val
            if (start->next == end) {
                // unique val, insert at tail
                if (tail == NULL) {
                    newhead = tail = start; tail->next = NULL;
                } else {
                    tail->next = start; tail = tail->next; tail->next = NULL;
                }
            } else {
                // do nothing
            }
        }
        return newhead;
    }
};
