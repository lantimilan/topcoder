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
    ListNode *rotateRight(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode dummy(0), *slow, *fast, *ptr, *tail;
        
        int n;
        for (n=0, ptr=head; ptr; ptr=ptr->next, ++n)
            ;
        if (n == 0) return head;
        k = k%n;
        // dummy starts new list
        // slow and fast used to find k-th node from the tail, 1-based        
        
        // slow + k = fast
        slow = fast = head;
        for (int i=0; i<k; ++i) {
            if (!fast) break;
            fast = fast->next;
        }
        if (!fast) return head;
        
        for (; fast; slow=slow->next, fast=fast->next) ;
        // slow points to k-th last node, 1-based
        
        tail = &dummy;
        for (ptr = slow; ptr; ptr=ptr->next) {
            tail->next = ptr; tail = tail->next;
        }
        for (ptr = head; ptr != slow; ptr = ptr->next) {
            tail->next = ptr; tail = tail->next;
        }
        tail->next = NULL;
        return dummy.next;
    }
};
