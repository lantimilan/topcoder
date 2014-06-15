/**
* search-in-rotated-sorted-array.cpp
* https://oj.leetcode.com/problems/search-in-rotated-sorted-array/
*/
class Solution {
public:
    int search(int A[], int n, int target) {
        int lo = 0, hi = n-1;
        while (lo + 1 < hi) {  // at least 3 elements in [lo..hi]
            int mid = (lo + hi) / 2;
            if (A[lo] < A[mid]) {  // max is to the right of mid, and A[lo..mid] is increasing
                if (A[lo] <= target && target <= A[mid]) hi = mid;
                else lo = mid;
            } else {  // A[lo] > A[mid], then max is to the left of mid, and A[mid..hi] is increasing
                if (A[mid] <= target && target <= A[hi]) lo = mid;
                else hi = mid;
            }
        }
        if (A[lo] == target) return lo;
        if (A[hi] == target) return hi;
        return -1;
    }
};
