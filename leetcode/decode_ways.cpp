class Solution {
public:
    vector<int> dp;
    int doit(const string &s, int l)
    {
        int r = s.size();
        if (l>=r) return 0;
        if (l+1 == r && s[l] > '0')
            return 1;
        if (l+2 == r) {
            int ans = 0;
            int val = (s[l]-'0') * 10 + s[l+1] - '0';
            if (s[l] > '0') {
                if (s[l+1]>'0') ans++;
                if (10 <= val && val <= 26) ans++;
            }
            return ans;
        }
        if (dp[l]>=0) return dp[l];
        int ans = 0;
        if (s[l] == '0') return 0; 
        ans += doit(s, l+1);
        if (l+1 < r) {
            int val = (s[l]-'0') * 10 + s[l+1] - '0';
            if (val <= 26)
                ans += doit(s, l+2);
        }
        return dp[l]=ans;
    }
    int numDecodings(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        dp.clear();
        dp.resize(s.size());
        fill(dp.begin(), dp.end(), -1);
        return doit(s, 0);
    }
};