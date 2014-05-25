/**
* word-break.cpp
* https://oj.leetcode.com/problems/word-break/
*/
class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
        int n = s.size();
        vector<bool> dp(n+1);  // dp[i] is true if the first i char can be split into words
        dp[0] = true;
        for (int i = 1; i <= n; ++i)
            for (int j = i-1; j >= 0; --j)
                if (dp[j] && dict.count(s.substr(j, i-j))) {
                    dp[i] = true; break;
                }
        return dp[n];
    }
};
