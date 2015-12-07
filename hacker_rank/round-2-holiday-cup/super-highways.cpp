// super-highways.cpp
#include <iostream>
using namespace std;

const int P = 1e9+9;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main() {
    int T; cin >> T;
    while (T--) {
    long long N, K, C; cin >> N >> K >> C;

    K %= P; C %= P;

    long long n = N-1;
    long long a[3] = {n, n+1, n+2};
    int deno = 6;
    for (int i = 0; i < 3; ++i) {
        long long g = gcd(a[i], deno);
        a[i] /= g; a[i] %= P;
        deno /= g;
    }
    long long ans = a[0] * a[1] % P * a[2] % P * K % P;

    long long b[2] = {N, N-1};
    if (b[0] % 2 == 0) b[0] /= 2;
    else b[1] /= 2;

    b[0] %= P; b[1] %= P;

    ans += b[0] * b[1] % P * C % P;
    cout << ans % P << endl;
    }
}
