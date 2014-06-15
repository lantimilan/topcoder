/**
* trapping-rain-water.cpp
* https://oj.leetcode.com/problems/trapping-rain-water/
*
*/
class Solution {
public:
    int trap(int A[], int n) {
        if (n <= 0) return 0;
        // left to right
        // find first nonzero column, then find next higher or equal column, trap water
        // do the same right to left
        int water = 0;
        int start, end, last;
        for (start = 0; start < n; ++start) if (A[start]) break;
        for (; start < n; start = end) {
            for (end = start + 1; end < n; ++end) if (A[end] >= A[start]) break;
            if (end >= n) break;
            int height = A[start];
            for (int i = start+1; i < end; ++i) water += height - A[i];
        }
        last = start;  // all water to the left of last has been collected
        // now right to left
        for (start = n-1; start > last; --start) if (A[start]) break;
        for (; start > last; start = end) {
            for (end = start-1; end >= last; --end) if (A[end] >= A[start]) break;
            if (end < last) break;
            int height = A[start];
            for (int i = start-1; i > end; --i) water += height - A[i];
        }
        return water;
    }
};
