/**
* sqrtx.cpp
* https://oj.leetcode.com/problems/sqrtx/
*
* integer overflow if hi is set to x+1
* integer overflow if we check mid * mid <= x
*/
class Solution {
public:
    int sqrt(int x) {
        assert(x >= 0);
        // binary search
        int lo = 0, hi = (x == 1) ? x+1 : x;  // invariant, lo * lo <= x and x < hi * hi
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;  // lo < mid < hi, so every iteration updates either lo or hi
            if (mid <= x / mid) lo = mid;  // might have integer overflow here
            else hi = mid;
        }
        return lo;
    }
};
