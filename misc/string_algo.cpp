// string_algo.cpp
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// the Z algorithm
// pre[pos] is the length of longest prefix starting at pos
// pre[0] = 0

vector<int> zalgorithm(string s)
{
    int n = s.size();
    vector<int> pre(n);
    pre[0] = 0;
    int start = 0;
    for (int pos = 1; pos < n; ++pos) {
        int span = pre[start];
        int end = start + span;
        if (pos >= end) {
            int p, j;
            for (p = pos, j = 0; p < n && s[p] == s[j]; ++p, ++j) ;
            pre[pos] = p - pos;
            start = pos;
        } else {
            int index = pos - start;
            if (pos + pre[index] < end) {
                // contained with span of start
                pre[pos] = pre[index];
            } else {
                int p, j;
                p = end; j = pre[index];
                for (; p < n && s[p] == s[j]; ++p, ++j) ;
                pre[pos] = p - pos;
                start = pos;
            }
        }
    }
    return pre;
}

void KMPcalc(const char *s, vector<int> &q)
{
    int m = 0;
    const char *p;
    for (p = s; *p; ++m, ++p) ;

    q.resize(m); q[0] = 0;
    for (int i = 1; i < m; ++i) {
        //cout << "i = " << i << endl;
        int k = i-1;
        while (k > 0 && s[i] != s[q[k]]) k = q[k]-1;
        if (s[i] == s[q[k]]) q[i] = q[k] + 1;
        else q[i] = 0;
    }
}

const char *KMPmatch(const char *text, const char *patt)
{
    int n, m;
    n = strlen(text); m = strlen(patt);
    vector<int> q;
    KMPcalc(patt, q);
    cout << "q function: ";
    for (int i = 0; i < m; ++i) cout << q[i] << ' '; cout << endl;
    int i, j;
    for (i = j = 0; i < n; ) {
        if (text[i] == patt[j]) {
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

int main()
{
    char text[100] = "aabc", patt[100] = "aabc";
    //scanf("%s%s", text, patt);
    printf("got text %s, patt %s\n", text, patt);
    const char *p = KMPmatch(text, patt);
    if (p) puts(p);
    else puts("No match");
}

/*
int main()
{
    string s; cin >> s;
    vector<int> pre = zalgorithm(s);
    for (int i = 0; i < s.size(); ++i) {
        cout << pre[i] << ' ';
    }
    cout << endl;
}
*/

/*
lyan@lyan-ThinkPad-T430:~/github/topcoder/misc$ ./a.out
aabbaab
0 1 0 0 3 1 0
*/
