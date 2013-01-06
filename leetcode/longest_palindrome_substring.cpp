class Solution {
public:
    string longestPalindrome(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = s.size();
        string ans;
        for (int p=1; p <= 2*n; ++p) {
            // odd p is letter
            // even p is gap
            int l, r, len;
            l = (p-1)/2;
            r = p/2;
            len = 0;
            if (p&1) {
                len++; l--; r++;
            }
            while (0<=l && r<n && s[l] == s[r]) {
                len += 2;
                --l; ++r;
            }
            if (len > ans.length()) {
                ans = s.substr(l+1, len);
            }            
        }
        return ans;
    }
};

// O(n^2) solution passed
// can do Manacher's in O(n)