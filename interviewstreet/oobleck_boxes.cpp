// oobleck_boxes.cpp
//
// Oobleck Boxes

#include <iostream>
using namespace std;

typedef long long int64;

const int MOD = 1e9+7;

int dp[1000000+5][30];
int64 mpow[30];

int main()
{
    int n, m; cin >> n >> m;
    if (m == 1) { cout << 1 << endl; return 0; }

    mpow[0] = 1;
    int k;
    for (k=1; ; ++k) {
        mpow[k] = mpow[k-1] * m;
        if (mpow[k] > n) break;
    }

    for (int j=0; j<k; ++j) dp[0][j] = 1;
    for (int i=1; i<=n; ++i)
    for (int j=0; j<k; ++j) {
        if (i >= mpow[j]) dp[i][j] = dp[i - mpow[j]][j];
        if (j > 0) dp[i][j] += dp[i][j-1];
        if (dp[i][j] >= MOD) dp[i][j] -= MOD;
    }
    cout << dp[n][k-1] << endl;
}

// Accepted
