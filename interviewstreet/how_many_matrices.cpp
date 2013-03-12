// how_many_matrices.cpp
//
// Knuth v3, Sorting and Searching
// 5.1.4
//
// number of tableaux with shape (n1, n2, ..., n_m)
// filled with number 1, 2, ..., n
// can be counted by
// n! / prod of all hook lengths
//
// hook length of an entry is the number of cells to its
// right and bottom, including itself
// for example
// a 2x3 tableau, entry (0,1) has hook length 2+2-1 = 3
//

#include <iostream>
#include <map>
using namespace std;

typedef long long int64;
const int MOD = 10007;

int fact(int n)
{
    int64 ans = 1;
    for (int i=2; i<=n; ++i)
        ans = (ans * i) % MOD;
    return ans;
}

int dblfact(int n)
{
    int64 ans = 1;
    for (int i=2; i<=n; ++i)
        ans = (ans * fact(i)) % MOD;
    return ans;
}

int fastpow(int a, int b)
{
    int64 ans = 1;
    int64 base = a;
    while (b) {
        if (b&1) ans = (ans * base) % MOD;
        base = base * base % MOD;
        b /= 2;
    }
    return ans;
}

int inv(int a)
{
    return fastpow(a, MOD-2);
}

int main()
{
    int N; cin >> N;
    if (N >= MOD) { cout << 0 << endl; return 0; }  // why count must be a multiple of N, No it is not
    int64 ans = 0;
    for (int d = 1; (int64)d * d <= N; ++d)
    if (N % d == 0)
    {
        int p, q, deno;
        int64 cur;
        p = d, q = N / d;
        //deno = dblfact(p+q-1);
        //cur = fact(N) * (int64)dblfact(p-1) * dblfact(q-1) % MOD * inv(deno) % MOD;
        cur = 1;
        for (int k=0; k<p; ++k)
            cur = cur * fact(q + k) * inv(fact(k)) % MOD;
        cur = fact(N) * inv(cur) % MOD;

        if (p == q) ans += cur;
        else ans += cur + cur;
        if (ans >= MOD) ans -= MOD;
    }
    cout << ans % MOD << endl;
}
