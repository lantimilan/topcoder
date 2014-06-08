/**
* unique-paths-ii.cpp
* https://oj.leetcode.com/problems/unique-paths-ii/
*/
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        if (obstacleGrid.empty()) return 0;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int> > dp(m, vector<int>(n));
        if (obstacleGrid[0][0] == 0) dp[0][0] = 1;
        for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (obstacleGrid[i][j] == 0) {
                if (i > 0) dp[i][j] += dp[i-1][j];
                if (j > 0) dp[i][j] += dp[i][j-1];
            }
        return dp[m-1][n-1];
    }
};
