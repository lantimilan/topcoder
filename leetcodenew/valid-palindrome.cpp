/**
* valid-palindrome.cpp
* https://oj.leetcode.com/problems/valid-palindrome/
*
*/
class Solution {
public:
    bool isPalindrome(string s) {
        int i, j;
        i = 0, j = s.length() - 1;
        for (; i < j; ++i, --j) {
            while (i < j && !isalnum(s[i])) ++i;
            if (i >= j) return true;
            while (j > i && !isalnum(s[j])) --j;
            if (i >= j) return true;
            if (tolower(s[i]) != tolower(s[j])) return false;
        }
        return true;
    }
};
