/**
* search-insert-position.cpp
* https://oj.leetcode.com/problems/search-insert-position/
*/
class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        int pos = n;
        for (int i = 0; i < n; ++i) {
            if (A[i] >= target) { pos = i; break; }
        }
        return pos;
    }
};
