/**
* single-number-ii.cpp
* https://oj.leetcode.com/problems/single-number-ii/
*/
class Solution {
public:
    int singleNumber(int A[], int n) {
        int ans = 0;
        for (int b = 0; b < 32; ++b) {
            int cur = 0;
            for (int i = 0; i < n; ++i){
                int bit = ((1<<b & A[i]) != 0);  // a tricky way to get 1 or 0 at this bit
                cur += bit;
                if (cur == 3) cur = 0;
            }
            ans |= cur << b;
        }
        return ans;
    }
};
