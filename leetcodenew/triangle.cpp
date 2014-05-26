/**
* triangle.cpp
* https://oj.leetcode.com/problems/triangle/
*/
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int n = triangle.size();
        vector<vector<int> > dp(n, vector<int>(n));
        dp[0][0] = triangle[0][0];
        for (int i = 1; i < n; ++i)
        for (int j = 0; j <= i; ++j) {  // dp[i][j] = a[i][j] + min(dp[i-1][j-1], dp[i-1][j])
            if (j == 0) {  // only one predecessor (i-1, j)
                dp[i][j] = dp[i-1][j] + triangle[i][j];
            } else {  // j > 0
                dp[i][j] = dp[i-1][j-1] + triangle[i][j];
                if (j <= i-1) {  // row i-1 has col <= i-1
                    int cur = dp[i-1][j] + triangle[i][j];
                    dp[i][j] = min(dp[i][j], cur);
                }
            }
        }
        int ans = dp[n-1][0];
        for (int j = 1; j < n; ++j)
            ans = min(ans, dp[n-1][j]);
        return ans;
    }
};
