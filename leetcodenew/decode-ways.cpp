/**
* decode-ways.cpp
* https://oj.leetcode.com/problems/decode-ways/
*/
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty()) return 0;
        vector<int> dp(s.length()+1);
        dp[0] = 1;
        dp[1] = (s[0] == '0') ? 0 : 1;
        for (int i = 2; i <= s.length(); ++i) {
            if (s[i-1] != '0') dp[i] += dp[i-1];
            int last = str2int(s.substr(i-2, 2));
            if (10 <= last && last <= 26) dp[i] += dp[i-2];
        }
        return dp[s.length()];
    }

    int str2int(string s) {
        int ans = 0;
        for (int i = 0; i < s.length(); ++i) ans = ans * 10 + s[i] - '0';
        return ans;
    }
};
