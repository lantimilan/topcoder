// prob554C.cpp
#include <iostream>
using namespace std;

const int M = 1e9+7;
int C[1005];
int dp[1005];
int comb[1005][1005];

void init() {
    comb[0][0] = 1;
    for (int n = 1; n <= 1000; ++n) {
        comb[n][0] = 1;
        for (int r = 1; r <= n; ++r) {
            comb[n][r] = comb[n-1][r] + comb[n-1][r-1];
            if (comb[n][r] >= M) comb[n][r] -= M;
        }
    }
}

int main() {
    init();
    int K; cin >> K;
    for (int i = 0; i < K; ++i) cin >> C[i];

    dp[0] = 1;
    int s = C[0];
    for (int i = 1; i < K; ++i) {
        int curr = 0;
        for (int j = 1; j <= C[i]; ++j) {
            curr += comb[C[i]-j + s-1][s-1];
            if (curr >= M) curr -= M;
        }
        dp[i] = 1LL * curr * dp[i-1] % M;
        s += C[i];
    }
    cout << dp[K-1] << endl;
}
