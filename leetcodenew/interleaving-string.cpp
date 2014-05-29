/**
 * interleaving-string.cpp
 * https://oj.leetcode.com/problems/interleaving-string/
 *
 * dp[i][j] is true if the first (i+j) char of s3 can be interleaved by the first i char in s1 and the first j char in s2
 * basecase: dp[0][0] = true
 * dp[i][j] = true if one of the following
 * dp[i-1][j] is true and s1[i-1] = s3[i+j-1]
 * dp[i][j-1] is true and s2[j-1] = s3[i+j-1]
 */
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size(), m = s2.size();
        if (s3.size() != n + m) return false;

        vector<vector<int> > dp(n+1, vector<int>(m+1, false));
        dp[0][0] = true;
        for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
        if (i != 0 || j != 0) {
            if (i-1 >= 0) {
                if (dp[i-1][j] && s1[i-1] == s3[i+j-1]) dp[i][j] = true;
            }
            if (j-1 >= 0) {
                if (dp[i][j-1] && s2[j-1] == s3[i+j-1]) dp[i][j] = true;
            }
        }
        return dp[n][m];
    }
};
