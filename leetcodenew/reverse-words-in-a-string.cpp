// reverse-words-in-a-string.cpp
// https://oj.leetcode.com/problems/reverse-words-in-a-string/

class Solution {
public:
    void reverseWords(string &s) {
        // clean up redundant space
        int start, end;
        for (start = 0; start < s.size() && s[start] == ' '; ++start)
            ;
        for (end = s.size()-1; end >= 0 && s[end] == ' '; --end)
            ;
        string t;
        char prev = ' ';
        for (int i = start; i <= end; ++i) {
            if (s[i] == ' ') {
                if (prev == ' ') {}
                else t += s[i];
            } else {
                t += s[i];
            }
            prev = s[i];
        }
        s = t;
        // first reverse string
        // then reverse each word
        for (int i = 0, j = s.size()-1; i < j; ++i, --j) {
            char ch = s[i]; s[i] = s[j]; s[j] = ch;
        }
        for (int i = 0; i < s.size(); ) {
            int j;
            for (j = i; j < s.size() && s[j] != ' '; ++j)
                ;
            // reverse s[i..j)
            for (int k = i, l = j-1; k < l; ++k, --l) {
                char ch = s[k]; s[k] = s[l]; s[l] = ch;
            }
            i = j+1;
        }
    }
};
