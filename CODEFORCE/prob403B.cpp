// prob403B.cpp
//
// 1. how to calculate score f(x) for number x
// let x = p1^r1 * p2^r2 * ...* pk^rk
// then f(x) = sum of +1 * r1 if p1 is good, else -1 * r1 if p1 is bad
//
// 2. notice that once we execute operation for a[1..l], the gcd for a[1..l]
// becomes 1, then no future operations are possible
// so we can have at most one operation.
// WRONG: we can have a[1..l], then do a[1..l1] for some l1 < l

#include <cassert>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;

int a[5005];
int b[5005];
set<int> bad;

int g[5005]; // g[i] is gcd of a[0..i] so g[0] = a[0] in particular

template<typename T>
void update(T &x, T y)
{
    if (x < y) x = y;
}

int gcd(int x, int y)
{
    if (x == 0) return y;
    else return gcd(y % x, x);
}

int calc(int x)
{
    int s = 0;
    for (int p = 2; p * p <= x; ++p) {
        int unit = 1;
        if (bad.count(p)) unit = -1;
        int cnt = 0;
        while (x % p == 0) {
            cnt++;
            x /= p;
        }
        s += unit * cnt;
    }
    if (x > 1) {
        if (bad.count(x)) s--;
        else s++;
    }
    return s;
}

int main()
{
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int j = 0; j < m; ++j) cin >> b[j];

    for (int j = 0; j < m; ++j) bad.insert(b[j]);

    g[0] = a[0];
    for (int i = 1; i < n; ++i) { g[i] = gcd(g[i-1], a[i]); }

    int best = -50 * 5000;  // score of each number if no less than -32, since 2^32 = 10^9
    for (int op = 0; op <= n; ++op) {
        int c[5005]; memcpy(c, a, sizeof(c));
        int divisor = 1;
        if (op > 0) divisor = g[op-1];
        for (int i = 0; i < op; ++i) {
            assert(c[i] % divisor == 0);
            c[i] /= divisor;
        }
        int score = 0;
        for (int i = 0; i < n; ++i) {
            score += calc(c[i]);
        }
        update(best, score);
    }
    cout << best << endl;
}
