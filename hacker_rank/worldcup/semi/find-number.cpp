// find-number.cpp
#include <iostream>
#include <map>
using namespace std;
// brute-force

long long N;
int A, B, C;
map<long long, long long> dp;

void chmax(long long &a, long long b) {
    if (a > b) a = b;
}

long long getcost(long long start, int incr) {
    return start + incr;
}

long long calc(long long n) {
    if (n <= 0) return -1e18;
    if (n == 1) return 0;
    if (dp.count(n)) return dp[n];

    dp[n] = 1e18;
    for (int p = 1; p < n; ++p)
    for (int q = p; q <= n; ++q) {
        long long first = calc(p) + A;
        long long second = calc(q-p) + B;
        long long third = calc(n-q) + C;
        long long curr = max(first, max(second, third));
        dp[n] = min(curr, dp[n]);
    }
    return dp[n];
}

void solve() {
    cin >> N;
    cin >> A >> B >> C;

    dp.clear();
    long long ans = calc(N);
    cout << ans << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
