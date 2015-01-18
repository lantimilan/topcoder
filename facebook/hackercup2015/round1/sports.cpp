// sports.cpp
#include <cassert>
#include <iostream>
using namespace std;

const int MOD = 1e9+7;
int good[2005][2005];
int bad[2005][2005];

void parse(string s, int &a, int &b) {
    int p;
    a = b = 0;
    for (p = 0; p < s.length() && s[p] != '-'; ++p) {
        a = 10 * a + s[p] - '0';
    }
    for (++p; p < s.length(); ++p) {
        b = 10 * b + s[p] - '0';
    }
}

void solve(int tcase) {
    string s; cin >> s;
    int a, b;
    parse(s, a, b);
    int first = good[a][b];
    int second = bad[b][b];
    cout << "Case #" << tcase << ": ";
    cout << first << ' ' << second << endl;
}

void init() {
    good[1][0] = 1;
    for (int a = 1; a <= 2000; ++a) {
        for (int b = 0; b < a; ++b) {
            good[a][b] += good[a-1][b];
            if (b > 0) good[a][b] += good[a][b-1];
            if (good[a][b] >= MOD) good[a][b] -= MOD;
        }
    }
    bad[0][0] = 1;
    for (int a = 0; a <= 2000; ++a) {
        for (int b = a; b <= 2000; ++b) {
            if (a > 0) bad[a][b] += bad[a-1][b];
            if (b > 0) bad[a][b] += bad[a][b-1];
            if (bad[a][b] >= MOD) bad[a][b] -= MOD;
        }
    }
    /*
    for (int a = 1; a <= 2000; ++a) {
        for (int b = 0; b <= 2000; ++b) {
            assert(good[a][b] == bad[b][a-1]);
        }
    }
    */
}

int main() {
    init();
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) solve(t);
}
