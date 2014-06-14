// wildcard-matching.cpp
//
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isMatch(const char *src, const char *patt) {
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
        // match the block in patt from its last '*' to end
        const char *send, *pend;
        for (send = src; *send; ++send) ;
        for (pend = patt; *pend; ++pend) ;
        for (s = --send, p = --pend; p > last; --s, --p) {
            if (!charMatch(*s, *p)) return false;
        }
        send = s+1; pend = p;  // now we work on src[0..send-1] and patt[0..pend-1], we know patt[pend] is '*'
        cout << "text end " << send - src << ' ' << "patt end" << pend - patt << endl;
        start = src;
        for (p = patt; *p; ) {
            // find the first segment start at nonstar and end with a '*'
            for (; *p && *p == '*'; ++p) ;
            if (!*p) return true;  // all nonstar in patt matched
            for (q = p+1; *q && *q != '*'; ++q) ;
            cout << "p q " << (p-patt) << ' ' << (q-patt) << endl;
            // now match patt[p..q-1] to src[start..send]
            const char *next = KMPmatch(start, send, p, q);
            cout << "next " << next - src << endl;
            if (next == NULL) return false;  // cannot find patt[p..q-1] in text[start..send-1]
            else start = next + (q-p);
            p = q+1;
        }
        return true;
    }

    void KMPcalc(const char *start, const char *end, vector<int> &q)
    {
        cout << "KMPcalc " << start << ' ' << end << endl;
        int m = end - start; cout << "KMPcalc m = " << m << endl;
        q.resize(m); q[0] = 0;
        for (int i = 1; i < m; ++i) {
            cout << "i = " << i << endl;
            int k = i-1;
            while (k > 0 && !charMatch(start[i], start[q[k]])) k = q[k]-1;  // this is critical, we know suffix end at k has prefix length q[k]
            // hence next pos to check is q[k]-1, which is of length q[k] for sub[0..q[k]-1]
            if (charMatch(start[i], start[q[k]])) q[i] = q[k] + 1;
            else q[i] = 0;
        }
        cout << "KMPcalc  done" << start << ' ' << end << endl;
    }
    const char *KMPmatch(const char *textStart, const char *textEnd, const char *pattStart, const char *pattEnd)
    {
        const char *text = textStart;
        const char *patt = pattStart;
        int n, m;
        n = textEnd - textStart; m = pattEnd - pattStart;
        vector<int> q;
        KMPcalc(pattStart, pattEnd, q);

        cout << pattStart << ' ' << pattEnd << endl;
        for (int i = 0; i < q.size(); ++i) cout << q[i] << ' '; cout << endl;

        int i, j;
        for (i = j = 0; i < n; ) {
            if (charMatch(text[i], patt[j])) {
                ++i, ++j;
                if (j >= m) {  // found patt
                    return text + (i-m);
                }
            } else {
                if (j == 0) ++i;
                else j = q[j];
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
    const char *text = "aabcdedefghijkl";
    const char *patt = "aabc*";
    bool good = sol.isMatch(text, patt);
    cout << text << ' ' << patt << ' ' << good << endl;
}
// TLE on "aaabbaabbaab", "*aabbaa*a*"
// TLE on (cleared, KMPcalc needs to move to q[k]-1 for next pos
