// LEVY.cpp
//
// gen all primes < 10^4
// then run p = all primes and q = all primes, update cnt[p + 2*q]
//
// since T is larger than N, precompute all queries

#include <iostream>
using namespace std;

bool isprime[10000];
int primes[10000];
int ans[10000+5];
int P;

void gen_prime(int cap)
{
    for (int i = 2; i < cap; ++i) isprime[i] = true;
    for (int i = 2; i < cap; ++i) if (isprime[i]) {
        primes[P++] = i;
        for (int j = i*i; j < cap; j += i) isprime[j] = false;
    }
}

void init(int cap)
{
    gen_prime(cap);
    for (int x = 0; x < P; ++x)
    for (int y = 0; y < P; ++y) {
        int a, b, c;
        a = primes[x]; b = primes[y];
        c = a + 2*b;
        if (c <= cap) ans[c]++;
    }
}

int main()
{
    int cap = 10000;
    init(cap);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        cout << ans[N] << endl;
    }
}
