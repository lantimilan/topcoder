// tutzki-and-lcs.cc
//
// given two strings, a and b, find the number of ways to insert a char
// into a such that lcs(a,b) increase by 1.
// length of a and b <= 5000.
//
// naive solution:
// for each pos in string a, insert some alnum and compute lcs.
// this is 5000 * 62 * 5000 * 5000, must TLE
// faster solution??
//
// some facts about lcs:
// 1. Is lcs unique?
// No, let A = "ab" and B = "ba", we have lcs being either "a" or "b"
//
// solution:
// we can insert char into pos=0..n for (n+1) different positions in string
// a, and that char must match some b[i] for i = 0..m-1, after that match,
// our lcs consists of lcs of the prefix and lcs of the suffix, plus one
// just matched.
// let pre[n1][m1] be the length of lcs for a[0..n1-1] and b[0..m1-1]
// and post[p1][q1] be the length of lcs for a[p1..n-1] and b[q1..m-1]
// then if we insert some char at apos and matches bpos
// our lcs is pre[apos][bpos] + post[apos][bpos+1] + 1
//
// pre and post can be computed once
// and we will check (n+1) positions in a to match m positions in b
// for a total of 5000 * 5000 = 2.5 * 10^7, which is fast enough.
//
// Now how large can the answer be, will it overflow int?
// the answer can be no more than 5000 pos in a, to match 5000 pos in b
// so will fit into 32-bit int.
//
// update1: got WA
// so the counting is wrong, if we insert ch='d' into pos = 3, and matched
// b[j1] and b[j2] both successfully, this counts only 1, not 2.

#include <iostream>
#include <set>
#include <string>
using namespace std;

int pre[5005][5005];
int post[5005][5005];

void chmax(int &a, int b) {
    if (a < b) a = b;
}

int main() {
    string a, b; cin >> a >> b;
    int n = a.length();
    int m = b.length();
    pre[0][0] = 0;
    post[n][m] = 0;
    for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= m; ++j) {
        if (i > 0 && j > 0) {
            int match = (a[i-1] == b[j-1]);
            chmax(pre[i][j], pre[i-1][j-1] + match);
        }
        if (i > 0) { chmax(pre[i][j], pre[i-1][j]); }
        if (j > 0) { chmax(pre[i][j], pre[i][j-1]); }
    }
    for (int i = n; i >= 0; --i)
    for (int j = m; j >= 0; --j) {
        if (i < n && j < m) {
            int match = (a[i] == b[j]);
            chmax(post[i][j], post[i+1][j+1] + match);
        }
        if (i < n) { chmax(post[i][j], post[i+1][j]); }
        if (j < m) { chmax(post[i][j], post[i][j+1]); }
    }

    int ans = 0;
    int old = pre[n][m];
    for (int apos = 0; apos <= n; ++apos) {
        set<char> st;
        for (int bpos = 0; bpos < m; ++bpos) {
            int lcs = pre[apos][bpos] + post[apos][bpos+1] + 1;
            if (lcs == old + 1) {
                st.insert(b[bpos]);
            }
        }
        ans += st.size();
    }
    cout << ans << endl;
}

// What is good?
// Found the right idea and had the correct algorithm.
// 
// What is bad?
// Did not read problem statement correctly.
