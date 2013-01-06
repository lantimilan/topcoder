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
    ListNode *partition(ListNode *head, int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode small(0), large(0);
        ListNode *p1, *p2;
        p1 = &small; p2 = &large;
        for (ListNode *p=head; p; ) {
            ListNode *q = p->next;
            if (p->val < x) { p1->next = p; p1 = p; }
            else { p2->next = p; p2 = p; }
            p->next = NULL;
            p = q;
        }
        p1->next = large.next;
        return small.next;
    }
};
