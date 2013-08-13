// SHIRO.cpp

// double dp[level][flag] = probability that army finished 1..level with flags
//
// ans is dp[N][(sum+1)/2]

#include <cassert>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

const int OFFSET = 100*100;
double dp[105][2*OFFSET + 5];

void solve()
{
    int N; cin >> N;
    int A[105], P[105], S[105];  // S[k+1] = A[0] + ... + A[k]
    S[0] = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        S[i+1] = S[i] + A[i];
    }
    for (int i = 0; i < N; ++i) cin >> P[i];

    memset(dp, 0, sizeof dp);
    dp[0][OFFSET] = 1.0;
    for (int i = 0; i < N; ++i) {
        for (int f = OFFSET-S[i]; f <= OFFSET+S[i]; ++f) {
            double prob = P[i] / 100.0;
            int next;
            // next is gain, prob = P[i] / 100.0
            next = f + A[i]; assert(next <= S[i+1] + OFFSET);
            dp[i+1][next] += dp[i][f] * prob;
            // next is lose, prob = 1 - P[i] / 100.0
            next = f - A[i]; assert(next >= 0);
            dp[i+1][next] += dp[i][f] * (1.0 - prob);
        }
    }
    double ans = 0.0;
    for (int k = OFFSET; k <= OFFSET + S[N]; ++k)
        ans += dp[N][k];
    cout << fixed << setprecision(10) << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--)
        solve();
}
