// movement-in-tree-ii.cpp
#include <iostream>
using namespace std;

const int M = 1e9+7;

int fastpow(int a, int p) {
    int b = a;
    int r = 1;
    while (p) {
        if (p&1) r = 1LL * r * b % M;
        p /= 2;
        b = 1LL * b * b % M;
    }
    return r;
}

int inv(int a) {
    return fastpow(a, M-2);
}

int main() {
    int T; cin >> T;
    while (T--) {
        long long d, k, h; cin >> d >> k >> h;
        long long d2 = 1LL * d * d % M;
        long long ss = 1LL * inv(d-1) * (fastpow(d, k+1) - 1) % M;
        long long s1 = 1LL * inv(d2-1) * fastpow(d2, k/2 + 1);
        long long s2 = (ss - s1 + M) % M;

        long long ans = 0;
        ans += 1LL * (fastpow(d, k+1) - 1) * v % M; //cout << ans << endl;
        h = min(k, h);
        ans += 1LL * fastpow(d, k-h) * (fastpow(d,h) -1) % M * v % M;
        cout << ans % M << endl;
    }
}
