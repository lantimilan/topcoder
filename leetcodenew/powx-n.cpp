/**
* powx-n.cpp
* https://oj.leetcode.com/problems/powx-n/
*
*/
class Solution {
public:
    double pow(double x, int n) {
        int sign = 1;
        if (n < 0) { sign = -1; n = -n; }

        double ans = 1.0;
        double base = x;
        while (n) {
            if (n & 1) ans *= base;
            base *= base;
            n /= 2;
        }
        if (sign > 0) return ans;
        else return 1.0 / ans;
    }
};
