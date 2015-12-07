// save-quantumland.cpp
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int b[105];
        for (int i = 0; i < n; ++i) cin >> b[i];
        int dp[105][2];
        for (int i = 0; i < n; ++i) dp[i][0] = dp[i][1] = 1000;
        dp[0][0] = 0;
        dp[0][1] = (b[0] ? 0 : 1);
        for (int i = 1; i < n; ++i) {
            if (b[i]) {
                dp[i][1] = min(dp[i-1][0], dp[i-1][1]);
            } else {
                dp[i][0] = dp[i-1][1];
                dp[i][1] = 1 + min(dp[i-1][0], dp[i-1][1]);
            }
        }
        cout << min(dp[n-1][0], dp[n-1][1]) << endl;
    }
}
