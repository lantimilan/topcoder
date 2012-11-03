/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// divide and conquer, O(nklogk)
// split into two halves and merge each half recursively
class Solution {
public:
    ListNode *mergeBase(ListNode *head1, ListNode *head2) {
        ListNode dummy(0);
        ListNode *p1, *p2, *p3;
        for (p1=head1, p2=head2, p3=&dummy; p1 && p2; ) {
            if (p1->val < p2->val) {
                p3->next = p1; p3 = p1; p1=p1->next;
            } else {
                p3->next = p2; p3 = p2; p2=p2->next;
            }
        }
        for (; p1; p1 = p1->next) { p3->next = p1; p3 = p1; }
        for (; p2; p2 = p2->next) { p3->next = p2; p3 = p2; }
        return dummy.next;
    }
    ListNode *mergeHelp(vector<ListNode *> &lists, int begin, int end) {
        if (end - begin == 1) return lists[begin];
        ListNode *head1, *head2;
        int mid = (begin+end)/2;
        head1 = mergeHelp(lists, begin, mid);
        head2 = mergeHelp(lists, mid, end);
        return mergeBase(head1, head2);
    }
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (lists.empty()) return NULL;
        int n = lists.size();
        return mergeHelp(lists, 0, n);
    }
};
