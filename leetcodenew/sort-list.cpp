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
    ListNode *sortList(ListNode *head) {
        // since O(nlogn), we use merge sort
        if (head == NULL || head->next == NULL) return head;
        // split in the middle
        // slow start at 0, move 1 step a time
        // fast start at 1, move 2 steps a time
        // stop if fast reaches NULL
        // we split into [0, slow) and [slow, end)
        //
        // if n = 2k, [0..2k-1] we want slow to stop at k-1, as a result, fast must reach NULL in k moves
        // if n = 2k+1, [0..2k] we want slow to stop at k-1, as a result, fast must reach NULL in k moves
        ListNode *slow, *fast;
        for (slow = head, fast = head->next;
            fast != NULL && fast->next != NULL;
            slow = slow->next, fast = fast->next->next) {
                // do nothing
        }
        ListNode *left = head, *right = slow->next;
        slow->next = NULL;
        left = sortList(left);
        right = sortList(right);
        // now merge two lists
        ListNode *newhead, *tail;
        if (left->val < right->val) {
            newhead = tail = left; left = left->next;
        } else {
            newhead = tail = right; right = right->next;
        }
        for (; left != NULL || right != NULL; tail = tail->next) {
            if (left == NULL) {
                tail->next = right; right = right->next;
            } else if (right == NULL) {
                tail->next = left; left = left->next;
            } else {
                if (left->val < right->val) {
                    tail->next = left; left = left->next;
                } else {
                    tail->next = right; right = right->next;
                }
            }
        }
        return newhead;
    }
};
