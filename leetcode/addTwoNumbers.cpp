/*
 * struct ListNode {
 *  int val;
 *  ListNode *next;
 *  ListNode(int x) : val(x), next(NULL) {}
 * };
 *
 */

class Solution {
 public:
    ListNode* addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode dummy(0);
        ListNode *p1, *p2, *tail;
        tail = &dummy;
        int carry = 0;
        for(p1=l1, p2=l2; p1 || p2; ) {
            int sum = carry;
            if (p1) { sum += p1->val; p1 = p1->next; }
            if (p2) { sum += p2->val; p2 = p2->next; }
            carry = sum/10;
            sum = sum % 10;
            ListNode *newnode = new ListNode(sum);
            tail->next = newnode;
            tail = newnode;
        }
        if (carry) {
            ListNode *newnode = new ListNode(carry);
            tail->next = newnode;
        }
        return dummy.next;
    }
};

// Accepted
