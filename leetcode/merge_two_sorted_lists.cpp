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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode dummy(0);
        ListNode *p1, *p2, *p3;
        for (p1=l1, p2=l2, p3=&dummy; p1 && p2; ) {
            if (p1->val < p2->val) { p3->next = p1; p3 = p1; p1 = p1->next; }
            else { p3->next = p2; p3 = p2; p2 = p2->next; }
        }
        for (; p1; p1 = p1->next) { p3->next = p1; p3 = p1; }
        for (; p2; p2 = p2->next) { p3->next = p2; p3 = p2; }
        return dummy.next;
    }
};