class Solution {
public:
    vector<vector<int>> dp;
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;

        int n = matrix.size();
        int m = matrix[0].size();
        dp = vector<vector<int>>(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int c1 = get_count(i-1, j);
            int c2 = get_count(i, j-1);
            int c3 = get_count(i-1, j-1);
            if (matrix[i][j] == '1') {
                dp[i][j] = min(c1, min(c2, c3)) + 1;
            }
        }

        int mx = 0;
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            mx = max(mx, dp[i][j]);
        }

        return mx * mx;
    }

    int get_count(int r, int c) {
        if (r < 0 || c < 0) return 0;
        else return dp[r][c];
    }
};
