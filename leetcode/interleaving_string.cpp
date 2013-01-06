class Solution {
public:
    vector<vector<int> > dp;
    
    bool isInterleave(string s1, string s2, string s3) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function        
        int n1 = s1.size();
        int n2 = s2.size();
        if (n1 + n2 != s3.size()) return false;
        dp.clear();
        dp.resize(n1+1);
        for (int i=0; i<dp.size(); ++i) {
            dp[i] = vector<int>(n2+1, 0);
        }
        dp[0][0] = 1;
        for (int i=0; i<=n1; ++i)
        for (int j=0; j<=n2; ++j)
        {
            if (i>0 && dp[i-1][j] && s1[i-1] == s3[i+j-1])
                dp[i][j] = 1;
            if (j>0 && dp[i][j-1] && s2[j-1] == s3[i+j-1])
                dp[i][j] = 1;
        }
        return dp[n1][n2] == 1;
    }
};