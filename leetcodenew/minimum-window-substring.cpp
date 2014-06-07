/**
* minimum-window-substring.cpp
* https://oj.leetcode.com/problems/minimum-window-substring/
*
*/
class Solution {
public:
    string minWindow(string S, string T) {
        int cnt[52] = {0};
        for (int i = 0; i < T.length(); ++i) {
            cnt[getcode(T[i])]++;
        }
        int Scnt[52] = {0};
        int first, second;  // invariant, S[first..second] is a substr contain T
        for (first = second = 0; second < S.length(); ++second) {
            char ch = S[second]; Scnt[getcode(ch)]++;
            if (check(Scnt, cnt, 52)) break;
        }
        if (second >= S.length()) return "";
        string wmin = S.substr(first, second - first + 1);
        for (++first; first < S.length(); ++first) {
            char ch = S[first-1]; Scnt[getcode(ch)]--;
            if (check(Scnt, cnt, 52)) {
                string cur = S.substr(first, second - first + 1);
                if (wmin.length() > cur.length()) wmin = cur;
                continue;
            }
            for (++second; second < S.length(); ++second) {
                char ch = S[second]; Scnt[getcode(ch)]++;
                if (check(Scnt, cnt, 52)) break;
            }
            if (second >= S.length()) break;
            else {
                string cur = S.substr(first, second - first + 1);
                if (wmin.length() > cur.length()) wmin = cur;
            }
        }
        return wmin;
    }

    bool check(int src[], int target[], int size) {
        for (int i = 0; i < size; ++i)
            if (src[i] < target[i]) return false;
        return true;
    }
    int getcode(char ch) {
        if ('a' <= ch && ch <= 'z') return 26 + ch - 'a';
        else return ch - 'A';
    }
};
