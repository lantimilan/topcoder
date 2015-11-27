// gg.cpp
#include <iostream>
using namespace std;

int N;
int M;
int dp[3005][3005];
int s[3005][3005];

int get_val(int n, int k) {
    return k >= 0 ? s[n][k] : 0;
}

int main() {
    cin >> N >> M;
    string S; cin >> S;
    dp[1][0] = 1;
    s[1][0] = 1;
    for (int i = 2; i <= N; ++i)
    for (int k = 0; k < i; ++k) {
        if (S[i-2] == 'G') {
            dp[i][k] = s[i-1][i-2] - get_val(i-1, k-1);
            if (dp[i][k] < 0) dp[i][k] += M;
        } else {
            dp[i][k] = get_val(i-1, k-1);
        }
        s[i][k] = get_val(i, k-1) + dp[i][k];
        if (s[i][k] >= M) s[i][k] -= M;
        //cout << i << ' ' << k << ' ' << dp[i][k] << ' ' << s[i][k] << endl;
    }

    cout << s[N][N-1] << endl;
}

