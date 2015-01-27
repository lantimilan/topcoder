// all_critical.cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int S = 20;
double dp[2][1<<20];

void solve(int tcase)
{
    double p; cin >> p; cout << "solve " << tcase << " " << p << endl;
    double ans = 0.0;
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1.0;
    for (int n = 0; n < 100; ++n) {
        int b = n & 1;
        memset(dp[1-b], 0, sizeof dp[0]);
        for (int mask = 0; mask < (1 << S); ++mask) {
            for (int s = 0; s < S; ++s) {
                dp[1-b][mask | 1<<s] += dp[b][mask] * p;
            }
        }
        ans += dp[1-b][(1<<S)-1] * (n+1);
    }
    // output solution
    cout << "Case #" << tcase << ": ";
    // sol here
    cout << fixed << setprecision(5) << ans;
    cout << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
