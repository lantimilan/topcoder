// MAXDIFF.cpp
//
// K = min(K, N-K)
// wmin = choose min weight K items
// ans = sum - wmin - wmin

#include <algorithm>
#include <iostream>
using namespace std;

int W[105];

void solve()
{
    int N, K; cin >> N >> K;
    if (K > N-K) K = N-K;
    for (int i = 0; i < N; ++i) cin >> W[i];
    sort(W, W+N);
    int wmin = 0;
    for (int i = 0; i < K; ++i) wmin += W[i];
    int sum = 0;
    for (int i = 0; i < N; ++i) sum += W[i];
    int ans = sum - 2*wmin;
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--)
        solve();
}
