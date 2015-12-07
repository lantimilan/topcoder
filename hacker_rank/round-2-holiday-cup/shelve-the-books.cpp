// shelve-the-books.cpp
#include <iostream>
using namespace std;

const int M = 1e9+7;

const int N = 1000000;
int pow8[N+5];
int fact[N+5];

void init() {
    pow8[0] = 1;
    for (int i = 1; i <= N; ++i) pow8[i] = pow8[i-1] * 8LL % M;
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = 1LL * fact[i-1] * i % M;
}

void solve() {
    int n, k; cin >> n >> k;
    int ans = 1LL * pow8[k] * fact[k] % M;
    if (n == k) ans = 3LL * ans % M;
    cout << ans << endl;
}

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
