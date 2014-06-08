/**
* length-of-last-word.cpp
* https://oj.leetcode.com/problems/length-of-last-word/
*
*/
class Solution {
public:
    int lengthOfLastWord(const char *s) {
        const char *p = s;
        for (; *p; ++p) ;
        for (--p; p >= s && *p == ' '; --p) ;
        if (p < s) return 0;
        const char *q;
        for (q = p-1; q >= s && *q != ' '; --q) ;
        return p - q;
    }
};
