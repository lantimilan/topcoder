// FCBARCA.cpp
//
// let Messi be player 0
// dp[N][last] is number of ways to make N passes end at last

#include <cstring>
#include <iostream>
using namespace std;

const int MOD = (int)(1e9+7);

int dp[1000+5][11];

int count(int N, int K)
{
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int p = 0; p < N; ++p)
    for (int last = 0; last <= K; ++last)
    for (int next = 0; next <= K; ++next) if (next != last) {
        dp[p+1][next] += dp[p][last];
        if (dp[p+1][next] >= MOD) dp[p+1][next] -= MOD;
    }
    int ans = dp[N][0];
    return ans;
}

int main()
{
    int T; cin >> T;
    while (T--) {
        int N, K; cin >> N >> K;
        int ans = count(N, K);
        cout << ans << endl;
    }
}


