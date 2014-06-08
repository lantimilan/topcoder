/**
* maximum-subarray.cpp
* https://oj.leetcode.com/problems/maximum-subarray/
*
*/
class Solution {
public:
    int maxSubArray(int A[], int n) {
        if (n == 0) return 0;
        int vmax = A[0];
        for (int i = 1; i < n; ++i) vmax = max(vmax, A[i]);
        if (vmax < 0) return vmax;

        int maxsum = 0;
        int start, end;  // [start..end-1] is nonnegative but [start..end] is negative
        for (start = 0; start < n; start = end + 1) {
            int sum = 0;
            for (end = start; end < n; ++end) {
                sum += A[end]; maxsum = max(maxsum, sum);
                if (sum < 0) break;
            }
        }
        return maxsum;
    }
};
