// 2,3,5,7 only
//

#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

typedef long long int64;

const int64 M = (1LL<<32)-1;

// use &M for mod

int base[] = {2,3,5,7};
int lim[] = {60,40,20,20};
int64 vals[100000+50]; int K;
int64 ways[20][100000]; // (len,val), ways to make val with len
int64 sums[20][100000];

void init()
{
    const int64 UPP = (int64)1e18;
    int s[4];
    int64 p[4];
    int64 prod = 1;
    for (s[0]=0, p[0]=1; s[0] < lim[0]; s[0]++, p[0] *= base[0])
    {
    prod = p[0];
    for (s[1]=0, p[1]=1; s[1] < lim[1]; s[1]++, p[1] *= base[1])
    {
    if (prod > UPP/p[1]) continue;
    prod *= p[1];
    for (s[2]=0, p[2]=1; s[2] < lim[2]; s[2]++, p[2] *= base[2])
    {
    if (prod > UPP/p[2]) continue;
    prod *= p[2];
    for (s[3]=0, p[3]=1; s[3] < lim[3]; s[3]++, p[3] *= base[3])
    {
    if (prod > UPP/p[3]) continue;
    prod *= p[3];
    vals[K++] = prod;
    prod /= p[3];
    }
    prod /= p[2];
    }
    prod /= p[1];
    }
    }
    printf("K %d\n", K);
    sort(vals, vals+K);
    for (int i=0; i<20; ++i) printf("%lld ", vals[i]); putchar('\n');
    for (int i=0; i<10; ++i) printf("%lld ", vals[K-1-i]); puts("");
    // validate only prime factors are 2,3,5,7
    for (int i=0; i<K; ++i) {
        int64 v = vals[i];
        for (int x=0; x<4; ++x) {
            while (v && v%base[x] == 0) v/=base[x];
        }
        assert(v==1);
    }
}

int get_id(int64 target)
{
    int l=0, r=K;
    while (l<r) {
        int m = (l+r)/2;
        if (vals[m] < target) l = m+1;
        else if (vals[m] > target) r = m;
        else return m;
    }
    return -1;
}

// return lower_bound
int get_lower(int64 a[], int n, int64 target)
{
    int l=-1, r=n; // invariant a[l] <= t and t < a[r]
    while (l+1 < r) {
        int m = (l+r)/2;
        if (a[m] <= target) l = m;
        else r = m;
    }
    assert(l+1 == r);
    return l;
}

void count_ways()
{
    const int L=18;
    ways[0][0] = 1;
    for (int len=1; len<=L; ++len)
    for (int x=0; x<K; ++x)
    {
    int64 ans = 0;
    int64 val = vals[x];
    for (int d=1; d<=9; ++d) if (val % d == 0)
    {
        int id = get_id(val/d);
        if (id >= 0) {
            ans += ways[len-1][id];
            ans &= M;
        }
    }
    ways[len][x] = ans;
    }
    int len = 2;
    for (int x=0; x<20; ++x) {
        printf("count_ways: %lld %d %lld\n", vals[x], len, ways[len][x]);
    }
}

int64 mypow(int base, int n)
{
    int64 ans = 1;
    for (int i=0; i<n; ++i)
        ans *= base;
    return ans;
}

int64 gcd(int64 a, int64 b)
{
    return b==0 ? a : gcd(b, a%b);
}

int main()
{
    init();
    count_ways();
    int T;
    int L;
    int64 V;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %lld", &L, &V); printf("%d %lld\n", L, V);
        int64 ans=0;
        int cap;
        if (L&1) cap = 9;
        else cap = 1;

        L /= 2;
        printf("cap %d L %d\n", cap, L);
        for (int m=1; m<=cap; ++m) {
            int g = gcd(V, m);
            int64 t = mypow(9,L)/(V/g);
            if (t < 1) continue;
            int x = get_lower(vals, K, t);
            printf("t %lld val[%d] %lld\n", t, x, vals[x]);
            assert(x>=0);
            for (int x=0; ; ++x) {
                int64 up = vals[x] * V;
                if (up > mypow(9,L)) break;
                int id = get_id(up);
                if (id>=0) {
                    ans += (ways[L][id] * ways[L][x] & M);
                    ans &= M;
                }
            }
            //ans += ways[L][x];
        }
        printf("%lld\n", ans);
    }
}
