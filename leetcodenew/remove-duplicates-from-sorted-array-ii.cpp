/**
* remove-duplicates-from-sorted-array-ii.cpp
* https://oj.leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
*
* first is the vacancy to insert
* second is the next unvisited element
*/
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        int first, second;
        for (first = second = 0; second < n; ++second) {
            if (first - 2 >= 0 && A[first-2] == A[second]) {}
            else A[first++] = A[second];
        }
        return first;
    }
};
