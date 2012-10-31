class Solution {
public:
    vector<vector<int> > dp;
    int calc(const string &S, const string &T, int l1, int l2)
    {
        if (l2 == T.size()) return 1;
        if (l1 == S.size()) return 0;
        if (dp[l1][l2] >= 0) return dp[l1][l2];
        int ans = 0;
        for (int i=l1; i<S.size(); ++i)
            if (S[i] == T[l2]) {
                ans += calc(S, T, i+1, l2+1);
            }
        return dp[l1][l2] = ans;
    }
    int numDistinct(string S, string T) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n, m;
        n = S.size(); m = T.size();
        dp.clear();
        dp.resize(n);
        for(int i=0; i<n; ++i)
            dp[i] = vector<int>(m,-1);
        return calc(S, T, 0, 0);
    }
};