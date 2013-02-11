// prob269B.cpp
// not submitted

#include <cstring>
#include <iostream>
using namespace std;

int dp[5005][5005];
int cnt[5005];
int a[5005];

int calc(int n, int m)
{
    if (n == 0) return 0;
    if (cnt[m] == 0) return calc(n, m-1);
    if (dp[n][m] >= 0) return dp[n][m];
    int p;
    for (p = n-1; a[p] != m; --p) ;
    a[p] = 100000;  cnt[m]--; // erase a[p];
    int ans = calc(p, m) + n-p-1;  // move [p+1..n-1]
    ans = min(ans, calc(n, m) + 1);
    return dp[n][m] = ans;
}

int main()
{
    memset(dp, -1, sizeof dp);
    int n; cin >> n;
    for (int i=0; i<n; ++i) {
        double x;
        cin >> a[i] >> x;
        cnt[a[i]]++;
    }
    int ans = calc(n, 5000);
    cout << ans << endl;
}
