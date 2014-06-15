/**
* search-for-a-range.cpp
* https://oj.leetcode.com/problems/search-for-a-range/
*/
class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> ans(2, -1);
        if (n <= 0) return ans;
        ans[0] = getFirst(A, n, target);
        ans[1] = getLast(A, n, target);
    }

    int getFirst(int A[], int n, int target) {
        int lo = -1, hi = n;  // A[lo] < target and target <= A[hi]
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (A[mid] < target) lo = mid;
            else hi = mid;
        }
        if (A[hi] == target) return hi;
        else return -1;
    }

    int getLast(int A[], int n, int target) {
        int lo = -1, hi = n;  // A[lo] <= target and target < A[hi]
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (A[mid] <= target) lo = mid;
            else hi = mid;
        }
        if (A[lo] == target) return lo;
        else return -1;
    }
};
