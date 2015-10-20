// restaurant-ratings.cpp
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int a[40];
long long dp[20][40];
long long dp2[20][40];

long long calc(int n, int s) {
    if (n == 0) return s == 0;
    if (dp[n][s] >= 0) return dp[n][s];

    dp[n][s] = 0;
    for (int v = 0; v <= s; ++v) {
        dp[n][s] += calc(n-1, s-v);
    }
    return dp[n][s];
}

long long calc2(int n, int s) {
    if (n == 0) return s == 0;
    if (dp2[n][s] >= 0) return dp2[n][s];

    dp2[n][s] = 0;
    for (int v = 0; v < a[n-1]; ++v) {
        dp2[n][s] += calc(n-1, s - v);
    }
    dp2[n][s] += calc2(n-1, s - a[n-1]);
    return dp2[n][s];
}

int main() {
    int tcase = 0;
    int n;
    while (cin >> n) {
        if (n == 0) break;
        memset(dp, -1, sizeof dp);
        memset(dp2, -1, sizeof dp2);
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            sum += a[i];
        }
        reverse(a, a+n);
        long long ans = 0;
        for (int s = 0; s < sum; ++s)
            ans += calc(n, s);
        ans += calc2(n, sum);
        cout << "Case " << (++tcase) << ": ";
        cout << ans << endl;
    }
}
