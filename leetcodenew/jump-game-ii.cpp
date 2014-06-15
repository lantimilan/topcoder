/**
* jump-game-ii.cpp
* https://oj.leetcode.com/problems/jump-game-ii/
*
*/
class Solution {
public:
    int jump(int A[], int n) {
        vector<int> dp(n, -1);
        dp[0] = 0;
        int last = 0;
        for (int i = 0; i < n; ++i) {
            int jump = A[i];
            for (int k = last+1; k < n && k-i <= jump; ++k) {  // notice that dp[] are monotonic
                dp[k] = dp[i] + 1; last = k;
            }
        }
        return dp[n-1];
    }
};
