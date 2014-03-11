// help-mike.cpp
//
#include <cassert>
#include <iostream>
using namespace std;

long long choose2(int n)
{
    return (long long)n * (n-1) / 2;
}

void solve()
{
    int N, K; cin >> N >> K; assert(K <= 10000 && K <= N);
    long long ans = 0;
    int cnt[10000+5] = {0};
    for (int m = 0; m < K; ++m) {
        int t = (N - m) / K;
        if (m != 0) t++;
        cnt[m] = t;
    }
    ans += choose2(cnt[0]);
    for (int x = 1; x <= (K-1)/2; ++x) {
        int y = K - x;
        ans += (long long)cnt[x] * cnt[y];
    }
    if (K % 2 == 0) ans += choose2(cnt[K/2]);
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--)
        solve();
}

// Accepted

