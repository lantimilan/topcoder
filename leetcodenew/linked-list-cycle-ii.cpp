/**
 * linked-list-cycle-ii.cpp
 * https://oj.leetcode.com/problems/linked-list-cycle-ii/
 *
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 *
 * solution:
 * two pointers, slow and fast, both start at head
 * slow moves 1 step at a time
 * fast moves 2 steps at a time
 * we stop when slow and fast meet
 * or fast reaches end and become NULL
 *
 * suppose they meet after k moves, then k must
 * be a multiple of len, the cycle length
 * To see this, we can imagine fast first follows
 * the moves of slow, then make additional k moves
 * of 1 step each, this will not change the meet point P.
 * In this modified fast pointer move, for the last k steps,
 * it starts at point P, and makes k moves of 1 step, and
 * stopped at P. So its last k steps completes cycles.
 *
 * Now let h be the number of steps from head to the entry
 * of cycle, call it E. We know that slow made k steps at stopped at P.
 * We also know that k is a multiple of len.
 * Let s be the number of steps from entry point E to meet point P
 * then h + s is a multiple of len.
 *
 * Let us assume we know h, then we can start from P and make h steps,
 * we will end up at entry point E. The problem is that we do not know h
 * But this is easy, we start another pointer, call it third.
 * We run both third and slow with 1 step, third will start at head, and slow
 * will start at P. When they meet, both travel h steps and the place they meet
 * is the entry point E.
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow, *fast, *third;
        if (head == NULL || head->next == NULL) return NULL;
        slow = head->next; fast = head->next->next;
        for (; fast != NULL && fast->next != NULL; slow = slow->next, fast = fast->next->next)
            if (slow == fast) break;
        if (fast == NULL || fast->next == NULL) return NULL;
        for (third = head; slow != third; slow = slow->next, third = third->next)
            ;
        return third;
    }
};
