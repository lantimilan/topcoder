class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int l, r;  // [l..r-1]
        int len, n;
        int cnt[26] = {0};
        l = r = 0;
        len = 0;
        n = s.length();
        for (; r < n; ++r) {
            char ch = s[r];
            while (cnt[ch - 'a']) {
                cnt[s[l]-'a']--; l++;
            }
            cnt[ch - 'a']++;
            len = max(len, r-l+1);
        }
        len = max(len, n - l);
        return len;
    }
};