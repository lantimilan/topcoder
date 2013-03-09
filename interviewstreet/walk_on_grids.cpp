// walk_on_grids.cpp
// dp

#include <iostream>
using namespace std;

const int MOD = 10007;
int dp[2005][2005];

int main()
{
    int N; cin >> N;
    int ans = 0;
    if (N==1) { cout << 1 << endl; return 0; }
    // upper
    for (int j=0; j<N; ++j) dp[0][j] = 1;
    for (int i=1; i<N; ++i) {
        for (int j=i; j<N; ++j) {
            dp[i][j] = dp[i-1][j];
            if (i <= j-1) dp[i][j] += dp[i][j-1];
            if (dp[i][j] >= MOD) dp[i][j] -= MOD;
        }
    }
    ans += dp[N-1][N-1];
    // lower
    for (int i=0; i<N; ++i) dp[i][0] = 1;
    for (int i=1; i<N; ++i) {
        for (int j=0; j<=i; ++j) {
            dp[i][j] = dp[i][j-1];
            if (i-1 >= j) dp[i][j] += dp[i-1][j];
            if (dp[i][j] >= MOD) dp[i][j] -= MOD;
        }
    }
    ans += dp[N-1][N-1];
    if (ans >= MOD) ans -= MOD;
    cout << ans << endl;
}

// Accepted
