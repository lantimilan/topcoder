/**
 * partition-list.cpp
 * https://oj.leetcode.com/problems/partition-list/
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
    ListNode *partition(ListNode *head, int x) {
        ListNode *smallhead, *largehead, *smalltail, *largetail;
        ListNode *p, *next;
        smallhead = smalltail = largehead = largetail = NULL;

        for (p = head; p != NULL; p = next) {
            next = p->next;
            if (p->val < x) {
                if (smalltail == NULL) { smallhead = smalltail = p; smalltail->next = NULL; }
                else { smalltail->next = p; smalltail = p; smalltail->next = NULL; }
            } else {
                if (largetail == NULL) { largehead = largetail = p; largetail->next = NULL; }
                else { largetail->next = p; largetail = p; largetail->next = NULL; }
            }
        }
        // now concat small and large
        if (smalltail == NULL) return largehead;
        else {
            smalltail->next = largehead;
            return smallhead;
        }
    }
};
