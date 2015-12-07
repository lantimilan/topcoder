// minimum-transformation-cost.cpp
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

string X, U;
int A, B, C;

void count_char(const string &s, int a[]) {
    for (char ch : s) {
        a[ch - 'a']++;
    }
}

void solve() {
    cin >> X >> U;
    cin >> A >> B >> C;  // (A, delete), (B, insert), (C, replace)

    int from[26] = {0};
    int to[26] = {0};

    count_char(X, from);
    count_char(U, to);

    int xlen = X.length();
    int ulen = U.length();

    int cost = 0;
    if (xlen > ulen) {
        int ndel = xlen - ulen; cost += A * ndel;
        for (int c = 0; c < 26; ++c) {
            if (from[c] > to[c]) {
                int diff = from[c] - to[c];
                int decr = min(diff, ndel);
                from[c] -= decr;
                ndel -= decr;
            }
        }
    } else if (xlen < ulen) {
        int nins = ulen - xlen; cost += B * nins;
        for (int c = 0; c < 26; ++c) {
            if (from[c] < to[c]) {
                int diff = to[c] - from[c];
                int incr = min(diff, nins);
                from[c] += incr;
                nins -= incr;
            }
        }
    }
    int unit = min(A + B, C);
    int cnt = 0;
    for (int c = 0; c < 26; ++c) {
        cnt += abs(from[c] - to[c]);
    }
    assert(cnt % 2 == 0);
    cost += unit * cnt / 2;
    cout << cost << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
