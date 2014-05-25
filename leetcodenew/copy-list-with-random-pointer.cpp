/**
 * copy-list-with-random-pointer.cpp
 * https://oj.leetcode.com/problems/copy-list-with-random-pointer/
 *
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 *
 * Two solutions:
 * 1. insert each node of copy list after their corresponding node in original list
 * 2. use hashmap to map node in original list to copy list
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == NULL) return NULL;
        RandomListNode *p, *q;
        // first insert copy nodes after their peers in original list
        for (p = head; p != NULL; p = q) {
            q = p->next;
            RandomListNode *copyNode = new RandomListNode(p->label);
            copyNode->next = p->next; p->next = copyNode;
        }
        // now set up random pointers for copy nodes
        for (p = head; p != NULL; p = p->next->next) {
            q = p->next;
            if (p->random != NULL) {
                q->random = p->random->next;
            }
        }
        // now extract copy nodes from merged list
        RandomListNode *copyHead, *copyTail;
        copyHead = copyTail = head->next;
        head->next = head->next->next;
        for (p = head->next; p != NULL; p = p->next) {
            q = p->next;
            copyTail->next = q; copyTail = copyTail->next;
            p->next = p->next->next;
        }
        return copyHead;
    }
};
