#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long int64;

int E, R, N;
int val[10000+5];
int dp[20][6];


void solve(int tcase)
{
    memset(dp, -1, sizeof dp);
    cin >> E >> R >> N;
    for (int i = 0; i < N; ++i) cin >> val[i];

    for (int l = 0; l <= E; ++l)
        dp[0][l] = (E-l) * val[0];
    for (int i = 1; i < N; ++i)
    for (int l = 0; l <= E; ++l)
    {
    for (int p = 0; p <= E; ++p)
    if (dp[i-1][p] >= 0)
    {
        int energy = min(E, p+R-l);
        int next = min(E, p+R) - energy;
        if (energy >= 0 && next >= 0) dp[i][next] = max(dp[i][next], dp[i-1][p] + energy * val[i]);
    }
    //cout << i << ' ' << l << ' ' << dp[i][l] << endl;
    }

    int ans = 0;
    for (int l = 0; l <= E; ++l)
        ans = max(ans, dp[N-1][l]);
    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}

// passed B-small
