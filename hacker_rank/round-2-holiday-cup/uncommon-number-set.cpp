// uncommon-number-set.cpp
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int P = 1e9+7;

int pow9[105];

void init() {
    pow9[0] = 1;
    for (int i = 1; i <= 100; ++i) pow9[i] = pow9[i-1] * 9LL % P;
}

int calc(const vector<int> &digits, int missing) {
    int n = digits.size();
    int dp[105];

    dp[0] = 1;
    for (int l = 1; l <= n; ++l) {
        int small = 0;
        for (int d = 0; d < digits[l-1]; ++d) {
            small += (d != missing);
        }
        //cout << "small " << small << ' ' << " missing " << missing << endl;
        int ans = 1LL * small * pow9[l-1] % P;
        if (digits[l-1] != missing) {
            ans += dp[l-1];
            if (ans >= P) ans -= P;
        }
        dp[l] = ans;
    }
    return (dp[n] + P - 1) % P;
}

int modint(const string &s) {
    int ans = 0;
    for (int i = 0; i < s.length(); ++i) {
        ans = (ans * 10LL + s[i]-'0') % P;
    }
    return ans;
}

int modsub(int a, int b) {
    return (a-b + P) % P;
}

void solve() {
    string N; cin >> N;
    int len = N.length(); //cout << "len " << len << endl;
    vector<int> digits;
    for (int i = 0; i < N.length(); ++i) {
        digits.push_back(N[len-1-i]-'0');
    }
    int total = modint(N);
    int ans = 0;
    for (int missing = 1; missing < 10; ++missing) {
        int cnt = calc(digits, missing);
        //cout << missing << ' ' << cnt << ' ' << total << endl;
        ans += 1LL * modsub(total, cnt) * cnt % P * missing % P;
        ans %= P;
        //cout << "missing " << missing << ' ' << ans << endl;
    }
    ans = ans * 2LL % P;
    cout << ans << endl;
}

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
