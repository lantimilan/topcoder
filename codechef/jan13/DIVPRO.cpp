// 2,3,5,7 only
//

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int64;

const int64 M = (1LL<<32)-1;

// use &M for mod

int base[] = {2,3,5,7};
int lim[] = {60,40,20,20};
int64 vals[100000+50]; int K;
int64 ways[20][100000]; // (len,val), ways to make val with len
int lookup[100000][12]; // (i,d) = j if vals[i]/d = vals[j]

void init()
{
    const int64 UPP = (int64)1e18;
    int s[4];
    int64 p[4];
    int64 prod = 1;
    for (s[0]=0, p[0]=1; s[0] <= lim[0]; s[0]++, p[0] *= base[0])
    {
    prod = p[0];
    for (s[1]=0, p[1]=1; s[1] <= lim[1]; s[1]++, p[1] *= base[1])
    {
    if (prod > UPP/p[1]) continue;
    prod *= p[1];
    for (s[2]=0, p[2]=1; s[2] <= lim[2]; s[2]++, p[2] *= base[2])
    {
    if (prod > UPP/p[2]) continue;
    prod *= p[2];
    for (s[3]=0, p[3]=1; s[3] <= lim[3]; s[3]++, p[3] *= base[3])
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
    //for (int i=0; i<20; ++i) printf("%lld ", vals[i]); putchar('\n');
    //for (int i=0; i<10; ++i) printf("%lld ", vals[K-1-i]); puts("");
    // validate only prime factors are 2,3,5,7
    //for (int i=0; i<K; ++i) {
    //    int64 v = vals[i];
    //    for (int x=0; x<4; ++x) {
    //        while (v && v%base[x] == 0) v/=base[x];
    //    }
    //    assert(v==1);
    //}

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

void init_table()
{
    puts("enter init table");
    // init lookup[i][d]
    memset(lookup, -1, sizeof lookup);
    for (int i=0; i<K; ++i)
    {
        int v = vals[i];
        lookup[i][1] = i;
        for (int d=2; d<10; ++d)
        {
            if (v % d == 0) {
                int id = get_id(v/d);
                if (id >= 0)
                    lookup[i][d] = id;
            }
        }
    }
    puts("done init table");
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
        //int id = get_id(val/d); // use lookup[i][d] table to speed up
        int id = lookup[x][d];
        if (id >= 0) {
            ans += ways[len-1][id];
            ans &= M;
        }
    }
    ways[len][x] = ans;
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

bool has_prime(int64 a)
{
    int base[] = {2,3,5,7};
    for (int x=0; x<4; ++x) {
        while (a % base[x] == 0)
            a /= base[x];
    }
    return a == 1LL;
}

void factorize(int64 a, int c[])
{
    //int64 b = a;
    int base[] = {2,3,5,7};
    for (int x=0; x<4; ++x) {
        while (a%base[x] == 0)
            a/=base[x], c[x]++;
    }
    //printf("%lld = 2^%d * 3^%d * 5^%d * 7^%d * %lld\n", b, c[0],c[1],c[2],c[3],a);
}

int main()
{
    init(); init_table();
    count_ways();
    int T;
    int L;
    int64 V;
    scanf("%d", &T);
    /*
    while (T--) {  // for T=320,000, takes 0.3s to do I/O
        scanf("%d %lld", &L, &V);
        printf("%d %lld\n", L, V);
        if (get_id(V) >= 0) {
            int64 cap = mypow(9,(L+1)/2);
            L /= 2;
        }
    }  
    return 0;  */


    // only K=60000 possible values of V
    // and only 36 values of L
    // precompute?
    while (T--) {
        scanf("%d %lld", &L, &V); printf("%d %lld\n", L, V);
        int64 ans=0;
        if (V==0) {
            int even, odd;
            odd = L/2; odd++;
            even = L - odd;
            ans = (mypow(10, even) - mypow(9, even));
            if (ans <0 ) ans += M;
            ans = ans * mypow(9, odd) & M;
            printf("%lld\n", ans);
            continue;
        }
        //if (has_prime(V)) {
        int L1, L2;
        L2 = L/2; L1 = L - L2;
        if (get_id(V) >= 0) {
            int64 cap = mypow(9,L1);
            for (int x=0; ; ++x) {
                if (cap / V < vals[x]) break;
                int64 up = vals[x] * V; assert(has_prime(up));
                int id = get_id(up);
                if (id >= 0)
                {
                    ans += (ways[L1][id] * ways[L2][x] & M);
                    ans &= M;
                }
            }
        }
        printf("%lld\n", ans);
    }
}
