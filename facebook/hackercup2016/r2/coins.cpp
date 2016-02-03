// coins.cpp
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

// (n,k) probability to land with exactly k heads with n coins
double prob[3005][3005];
double cum[3005];
double dp[3005]; // expected prize with n coins
int N, K;
double P;

void calc() {
    for (int i = 0; i <= N; ++i) prob[0][i] = 0.0;
    prob[0][0] = 1.0;

    for (int i = 1; i <= N; ++i)
    for (int j = 0; j <= N; ++j) {
        prob[i][j] = (1-P) * prob[i-1][j];
        if (j > 0) prob[i][j] += P * prob[i-1][j-1];
    }

    for (int i = 0; i <= N; ++i) {
        cum[i] = 0.0;
        for (int j = K; j <= N; ++j) {
            cum[i] += prob[i][j];
        }
    }
}

void chmax(double &a, double b) {
    if (a < b) a = b;
}

void solve(int tcase) {
    cin >> N >> K >> P;
    calc();

    dp[0] = 0;
    for (int i = 1; i <= N; ++i) {
        dp[i] = cum[i];
        for (int j = 1; j < i; ++j) {
            chmax(dp[i], dp[j] + dp[i-j]);
        }
    }
    // output
    cout << "Case #" << tcase << ": ";
    cout << fixed << setprecision(9) << dp[N] << endl;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
