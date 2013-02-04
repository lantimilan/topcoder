// A.cpp

#include <algorithm>
#include <iostream>
using namespace std;

typedef long long int64;

int A[10000+5];

const int MOD = 1e9+7;

int add(int a, int b)
{ return ((int64)a + b) % MOD; }

int mult(int a, int b)
{ return (int64)a * b % MOD; }

int fastpow(int a, int n)
{
    int ans = 1;
    int base = a;
    while (n) {
        if (n & 1) ans = mult(ans, base);
        base = mult(base, base);
        n /= 2;
    }
    return ans;
}

int inv(int a)
{
    return fastpow(a, MOD-2);
}

void solve(int tcase)
{
    int N, K; cin >> N >> K;
    for (int i=0; i<N; ++i) cin >> A[i];
    sort(A, A+N);
    int coeff = 1;
    int ans = 0;
    for (int i=K-1; i<N; ++i) {
        ans = add(ans, mult(coeff, A[i]));
        coeff = mult(coeff, i+1);
        coeff = mult(coeff, inv((i+1)-(K-1)));
    }
    cout << "Case #" << tcase << ": " << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t=1; t<=T; ++t)
        solve(t);
}
