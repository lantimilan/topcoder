/**
* distinct-subsequences.cpp
* https://oj.leetcode.com/problems/distinct-subsequences/
*
*/
class Solution {
public:
    int numDistinct(string S, string T) {
        int n = S.size(), m = T.size();
        vector<vector<int> > dp(n+1, vector<int>(m+1));  // dp[i][j] is the number of subsequence in prefix of length i of S, of prefix of length j in T
        dp[0][0] = 1;  // dp[0][j] = 0 for all j >= 1
        for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = dp[i-1][j];  // not use S[i-1]
            if (j > 0 && S[i-1] == T[j-1]) dp[i][j] += dp[i-1][j-1];
        }
        return dp[n][m];
    }
};
