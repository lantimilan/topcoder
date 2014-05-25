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
    ListNode *insertionSortList(ListNode *head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode *newhead, *tail, *next;
        newhead = tail = head; head = head->next;
        tail->next = NULL;
        for (; head != NULL; head = next) {
            next = head->next;
            // insert head into newhead list
            if (head->val < newhead->val) { // insert at head
                head->next = newhead; newhead = head;
            } else { // insert after head
                ListNode *p = newhead;
                while (p->next != NULL && p->next->val <= head->val) p = p->next;
                ListNode *pp = p->next;
                p->next = head; head->next = pp;
            }
        }
        return newhead;
    }
};
