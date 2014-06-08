/**
* minimum-path-sum.cpp
* https://oj.leetcode.com/problems/minimum-path-sum/
*/
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        if (grid.empty()) return 0;
        int n = grid.size(), m = grid[0].size();
        vector<vector<int> > dp(n, vector<int>(m, -1));
        dp[0][0] = grid[0][0];
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            if (i > 0) update(dp[i][j], dp[i-1][j] + grid[i][j]);
            if (j > 0) update(dp[i][j], dp[i][j-1] + grid[i][j]);
        }
        return dp[n-1][m-1];
    }
    void update(int &a, int b) {
        if (b >= 0) {
            if (a < 0 || a > b) a = b;
        }
    }
};
