// wildcard-matching.cpp
//
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isMatch(const char *src, const char *patt) {
        //assert(false); assertion fail will give RE
        if (src == NULL && patt == NULL) return true;
        if (src == NULL || patt == NULL) return false;
        if (*src == '\0' && *patt == '\0') return true;
        if (*src == '\0' || *patt == '\0') return false;

        // now src and patt are of length at least 1

        // this seems to require some linear time pattern matching algorithm such as KMP or Z-algorithm
        // solution: first match the suffix in patt starting from last *
        // then use * to split patt into pieces and find the first match in src for each piece
        const char *s, *p, *q;
        const char *last = NULL, *start;
        // find the last '*' in patt
        for (p = patt; *p; ++p) if (*p == '*') last = p;
        if (last == NULL) {  // patt has no '*', simple char by char match
            for (s = src, p = patt; *s && *p; ++s, ++p) {
                if (!charMatch(*s, *p)) return false;
            }
            if (*s || *p) return false;
            return true;
        }
        // match the block in patt from ist last '*' to end
        const char *send, *pend;
        for (send = src; *send; ++send) ;
        for (pend = patt; *pend; ++pend) ;
        cout << (send - src) << ' ' << (pend - patt) << endl;
        for (s = --send, p = --pend; p > last; --s, --p) {
            if (s < src) return false;
            if (!charMatch(*s, *p)) return false;
        }
        send = s+1; pend = p;  // now we work on src[0..send-1] and patt[0..pend-1], we know patt[pend] is '*'
//cout << send - src << ' ' << pend - patt << endl;
        // first match prefix of src[0..send-1] and prefix of patt[0..pend-1] where prefix stops at first '*' in patt
        for (start = src, p = patt; p < pend; ++start, ++p) {
            if (*p == '*') break;
            if (!charMatch(*start, *p)) return false;  // this also covers when src[] is shorter than patt[0..first'*'-1]
        }

        // now p points to the first '*' in patt, there must be one '*' because we found last points to the last '*' earlier
        for (; p < pend; ) {
            // find the first segment start at nonstar and end with a '*'
            for (; p < pend && *p == '*'; ++p) ;  // find the first nonstar char in patt[p..pend-1]
            if (p >= pend) return true;  // all nonstar in patt matched
            for (q = p+1; q <= pend && *q != '*'; ++q) ;  // find the terminating '*' for the block in patt[p..pend-1]
            if (start >= send) return false;  // text must be nonempty
            // now match patt[p..q-1] to src[start..send]
            const char *next = KMPmatch(start, send, p, q);
            if (next == NULL) return false;  // cannot find patt[p..q-1] in text[start..send-1]
            else start = next + (q-p);
            p = q+1;
        }
        return true;
    }

    void KMPcalc(const char *start, const char *end, vector<int> &q)
    {
        int m = end - start;
        q[0] = 0;
        for (int i = 1; i < m; ++i) {
            int k = i-1;
            while (k > 0 && !charMatch(start[i], start[q[k]])) k = q[k]-1;
            if (start[i] == start[q[k]]) q[i] = q[k] + 1;
            else q[i] = 0;
        }
    }
    const char *KMPmatch(const char *textStart, const char *textEnd, const char *pattStart, const char *pattEnd)
    {
        const char *text = textStart;
        const char *patt = pattStart;
        int n, m;
        n = textEnd - textStart; m = pattEnd - pattStart;  //if (n < 1 || m < 1) return NULL;
        //assert(n > 0 && m > 0);
        vector<int> q(m);
        KMPcalc(pattStart, pattEnd, q);

        int i, j;
        for (i = j = 0; i < n; ) {
            if (charMatch(text[i], patt[j])) {
                ++i, ++j;
                if (j >= m) {  // found patt
                    return text + (i-m);
                }
            } else {
                if (j == 0) ++i;
                else j = q[j-1];
            }
        }
        return NULL;
    }

    bool charMatch(char c1, char c2) {
        if (c1 == '?' || c2 == '?') return true;
        return c1 == c2;
   }
};
int main()
{
    Solution sol;
    const char *text = "aaaababaabaaababbaabaaabbbbabbabaabbbbbbaababbbaaa";
    const char *patt = "*aabbaa**";
    //const char *patt = "*aabbaa**";
    //const char *text = "baababbaaaaabbababbbbbabaabaabaaabbaabbbbbbaabbbaaabbabbaabaaaaabaabbbaabbabababaaababbaaabaababbabaababbaababaabbbaaaaabbabbabababbbbaaaaaabaabbbbaababbbaabbaabbbbbbbbabbbabababbabababaaababbaaababaabb";
    //const char *patt = "*ba***b***a*ab**b***bb*b***ab**aa***baba*b***bb**a*abbb*aa*b**baba**aa**b*b*a****aabbbabba*b*abaaa*aa**b";
    bool good = sol.isMatch(text, patt);
    cout << text << ' ' << patt << ' ' << good << endl;
}


// RE clear
//    const char *text = "bbbbbbbabaabaaabaaaaaabbbabbabbaaabbbabaabbababbabaaabbbbaaabbabbbaabbabbabaaaaaaaaabbbabbabaaabbbbaabbbbaabbabbabbbaabababbabaaababaaaaaabbabaaabbbbbbababbbbbaaabbabbaaaaababaaabbbaaaababbbbbbaababaaa";
//    const char *patt = "**b*bb*aa*baaaa*aaa*b*baaa*a*aaa*b*a*ba**ba*ba*ba*b*b****a*ba*b**a*****ba*bb*a***abb***a*bb***b**abb*";
// RE on "bbbbbbbabaabaaabaaaaaabbbabbabbaaabbbabaabbababbabaaabbbbaaabbabbbaabbabbabaaaaaaaaabbbabbabaaabbbbaabbbbaabbabbabbbaabababbabaaababaaaaaabbabaaabbbbbbababbbbbaaabbabbaaaaababaaabbbaaaababbbbbbaababaaa", "**b*bb*aa*baaaa*aaa*b*baaa*a*aaa*b*a*ba**ba*ba*ba*b*b****a*ba*b**a*****ba*bb*a***abb***a*bb***b**abb*"
// TLE on "aaabbaabbaab", "*aabbaa*a*", cleared, set j = q[j-1] in KMPmatch
// TLE on (cleared, KMPcalc needs to move to q[k]-1 for next pos
