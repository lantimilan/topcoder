/**
* palindrome-partitioning-ii.cpp
* https://oj.leetcode.com/problems/palindrome-partitioning-ii/
*
* O(n^2) algorithm to find all substr palindromes
*/
class Solution {
public:
    int minCut(string s) {
        int n = s.length();
        vector<vector<bool> > is_pal(n+1, vector<bool>(n+1, false));
        init(s, is_pal);
        vector<int> cuts(n+1, -1);
        cuts[0] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = i-1; j >= 0; --j) if (is_pal[j][i]) {
                if (cuts[i] < 0) cuts[i] = cuts[j] + 1;
                else if (cuts[i] > cuts[j] + 1) cuts[i] = cuts[j] + 1;
            }
        return cuts[n]-1;
    }

    void init(const string &s, vector<vector<bool> > &is_pal) {
        vector<int> oddlen(s.size()+1, 0);
        vector<int> evenlen(s.size()+1, 0);
        for (int i = 0; i < s.size(); ++i) {
            oddlen[i] = 1;
            for (int j1 = i-1, j2 = i+1; 0 <= j1 && j2 < s.size(); --j1, ++j2) {
                if (s[j1] == s[j2]) oddlen[i] += 2;
                else break;
            }
        }
        for (int i = 0; i <= s.size(); ++i) {
            evenlen[i] = 0;
            for (int j1 = i-1, j2 = i; 0 <= j1 && j2 < s.size(); --j1, ++j2) {
                if (s[j1] == s[j2]) evenlen[i] += 2;
                else break;
            }
        }

        for (int i = 0; i < s.size(); ++i)
        for (int j = i+1; j <= s.size(); ++j) {
            int center = (i+j) / 2;
            if (i%2 == j%2) {
                // even segment
                if (evenlen[center] >= j-i) is_pal[i][j] = true;
            } else {
                if (oddlen[center] >= j-i) is_pal[i][j] = true;
            }
        }
    }
};
