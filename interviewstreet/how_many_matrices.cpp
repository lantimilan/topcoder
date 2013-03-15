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

#include <cassert>
#include <iostream>
#include <map>
using namespace std;

typedef long long int64;
const int MOD = 10007;
map<int,int> memo;

// return k such that p^k is the largest power of p that divides n
int count_pow(int n, int p)
{
    int ans = 0;
    while (n) {
        ans += n/p;
        n/=p;
    }
    return ans;
}

int ppfact(int n, int p)
{
    assert(memo.count(n));
    return memo[n];
}

void init(int n, int p)
{
    int cur = 1;
    for (int i=1; i<=n; ++i) {
        int k = i;
        while (k % p == 0) k /= p;
        cur = cur * k % p;
        if (memo.count(i)) memo[i] = cur;
    }
}

int fastpow(int a, int b)
{
    int ans = 1;
    int base = a;
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
    int ans = 0;
    for (int d = 1; (int64)d * d <= N; ++d)
    if (N % d == 0)
    {
        memo[N / d] = 0;
    }
    init(N, MOD);

    int pre, cnt;
    pre = ppfact(N, MOD);
    cnt = count_pow(N, MOD);
    for (int d = 1; (int64)d * d <= N; ++d)
    if (N % d == 0)
    {
        int p, q;
        p = d, q = N / d;

        int prod = 1;
        int term = ppfact(q, MOD);
        int bottom = count_pow(q, MOD);
        for (int i=1; i<=p; ++i) {
            prod = prod * term % MOD;
            int next = q+i;
            while (next % MOD == 0) { bottom++; next /= MOD; }
            term = term * next % MOD;
            int k = i;
            while (k % MOD == 0) { bottom--; k /= MOD; }
            term = term * inv(k) % MOD;
        }
        int cur;
        if (cnt > bottom) { cur = 0; }
        else { cur = pre * inv(prod) % MOD; }

        if (p == q) ans += cur;
        else ans += cur + cur;
        if (ans >= MOD) ans -= MOD;
    }
    cout << ans % MOD << endl;
}
