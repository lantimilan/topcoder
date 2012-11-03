class Solution {
public:
    void update(int &a, int b)
    {
        if (b>=0) {
            if (a<0) a = b;
            else if (a>b) a = b;
        }
    }
    int minPathSum(vector<vector<int> > &grid) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int> > dp = grid;
        for (int i=0; i<n; ++i)
        for (int j=0; j<m; ++j)
            dp[i][j] = -1;
        
        dp[0][0] = grid[0][0];
        for (int i=0; i<n; ++i)
        for (int j=0; j<m; ++j)
        {
            if (i>0 && dp[i-1][j] >= 0)
                update(dp[i][j], dp[i-1][j] + grid[i][j]);
            if (j>0 && dp[i][j-1] >= 0)
                update(dp[i][j], dp[i][j-1] + grid[i][j]);                
        }
        return dp[n-1][m-1];
    }
};