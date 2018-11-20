// MAXPRODU.cc
// AC
// Quite lucky, the optimization in prod() is not needed and could lead to
// fact[] out of bounds. But got lucky and accepted with the wrong code.
// prod2() is what the problem setter is looking for.
#include <cassert>
#include <iostream>
using namespace std;

const int MOD = 1e9+7;
const int MX = 2000000;

// largest fact is N=10^9 and K=10^4
int fact[MX+5];
int inv[MX+5];


// return a^b % MOD
int fastpow(int a, int b) {
    int ans = 1;
    int f = a;
    while (b) {
        if (b&1) ans = 1LL * f * ans % MOD;
        b >>= 1;
        f = 1LL * f * f % MOD;
    }
    return ans;
}

void init() {
    fact[0] = fact[1] = 1;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < MX; ++i) {
        fact[i] = 1LL * fact[i-1] * i % MOD;
        inv[i] = fastpow(fact[i], MOD-2);
        // if (i < 10) cout << "init " << i << ' ' << fact[i] << ' ' << inv[i] << endl;
    }
}

// return a * (a+1) * ... * b
int prod(int a, int b) {
    // cerr << "prod " << a << ' ' << b << endl;
    assert(a >= 0);
    if (a == 0) return 0;
    if (b-a <= 1000) {
        int ans = 1;
        for (int i = a; i <= b; ++i) {
            ans = 1LL * ans * i % MOD;
        }
        return ans;
    }
    return 1LL * fact[b] * inv[a-1] % MOD;
}

int prod2(int a, int b) {
    if (a == 0) return 0;
        int ans = 1;
        for (int i = a; i <= b; ++i) {
            ans = 1LL * ans * i % MOD;
        }
        return ans;
}

void solve() {
    int N, K; cin >> N >> K;
    // must be 1,2,...,K, then apply the remaining balance from high to low
    // K is 10^4
    int sum = (1 + K) * K / 2;
    if (sum > N) {
        cout << -1 << endl;
        return;
    }
    int b = (N - sum) / K;
    int r = (N - sum) % K;
    // cout << "sum,b,r " << sum << " " << b << " " << r << endl;
    // now we have (1+b), (2+b), ... (K-r+b), (K-r+1+b+1) ... (K+b+1)
    // the product is x1,x2,..xK * (x1-1),...(xK-1)
    int ans = 1LL * prod2(1+b, K-r+b) % MOD; // cout << "ans1 " << ans << endl;
    ans = 1LL * ans * prod2(b, K-r+b-1) % MOD; // cout << "ans2 " << ans << endl;
    if (r > 0) {
        ans = 1LL * ans * prod2(K-r+1+b+1, K+b+1) % MOD;
        // cout << "ans3 " << ans << endl;
        ans = 1LL * ans * prod2(K-r+1+b, K+b) % MOD;
        // cout << "ans4 " << ans << endl;
    }
    cout << ans << endl;
}

int main() {
    // init(); // only needed for prod()
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
