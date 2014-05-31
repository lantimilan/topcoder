/**
* unique-binary-search-trees.cpp
* https://oj.leetcode.com/problems/unique-binary-search-trees/
*
*/
class Solution {
public:
    int numTrees(int n) {
        // dp[n][i] is the number of binary search tree with n nodes, and rooted at i
        // dp2[n] is the number of binary search tree with n nodes
        // dp[n][i] = dp2[i-1] * dp2[n-i]
        // dp2[n] = sum dp[n][i] for i = 1 to n
        // basecase: dp2[0] = 1

        vector<vector<int> > dp(n+1, vector<int>(n+1));
        vector<int> dp2(n+1);
        dp2[0] = 1;
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= k; ++i) {
                dp[k][i] = dp2[i-1] * dp2[k-i];
                dp2[k] += dp[k][i];
            }
        }
        return dp2[n];
    }
};
