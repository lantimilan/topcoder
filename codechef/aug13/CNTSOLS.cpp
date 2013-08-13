// CNTSOLS.cpp

#include <iostream>
using namespace std;

int fastpow(int a, int b, int m)
{
    int ans = 1;
    int base = a;
    while (b) {
        if (b & 1) ans = ans * base % m;
        base = base * base % m;
        b /= 2;
    }
    return ans;
}

void solve()
{
    const int MOD = 1e9+7;
    int ans = 0;
    int upper, d, m, N;
    cin >> upper >> d >> m >> N;
    int cap = min(N, upper+1);
    for (int x1 = 0; x1 < cap; ++x1)
    for (int x2 = 0; x2 < cap; ++x2)
    for (int x3 = 0; x3 < cap; ++x3)
    {
        int p1, p2, p3;
        p1 = fastpow(x1, d, N);
        p2 = fastpow(x2, d, N);
        p3 = fastpow(x3, d, N);
        if ((p1 + p2 + p3) % N == m) {
            long long c[3], t;
            c[0] = (upper - x1) / N + 1;
            c[1] = (upper - x2) / N + 1;
            c[2] = (upper - x3) / N + 1;
            t = c[0] * c[1] % MOD;
            t = t * c[2] % MOD;
            ans += t;
            if (ans >= MOD) ans -= MOD;
        }
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--)
        solve();
}

// simpler than I thought
// Correct Answer
// Execution Time: 0.54
