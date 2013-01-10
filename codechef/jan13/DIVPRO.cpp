// 2,3,5,7 only
//

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
using namespace std;

typedef long long int64;

const int64 M = (1LL<<32)-1;

// use &M for mod

typedef pair<int64,int64> pii;
int base[] = {2,3,5,7};
int lim[] = {60,40,20,20};
int64 vals[1000000+50]; int K;
map<pii, int64> ways; // (len,val), ways to make val with len
map<pii, int64> sums;

void init()
{
    const int64 UPP = 1e18;
    int s[4];
    int64 p[4];
    int64 prod = 1;
    for (s[0]=0, p[0]=1; s[0] < lim[0]; s[0]++, p[0] *= base[0])
    {
    prod = p[0];
    for (s[1]=0, p[1]=1; s[1] < lim[1]; s[1]++, p[1] *= base[1])
    {
    if (prod >= UPP/p[1]) continue;
    prod *= p[1];
    for (s[2]=0, p[2]=1; s[2] < lim[2]; s[2]++, p[2] *= base[2])
    {
    if (prod >= UPP/p[2]) continue;
    prod *= p[2];
    for (s[3]=0, p[3]=1; s[3] < lim[3]; s[3]++, p[3] *= base[3])
    {
    if (prod >= UPP/p[3]) continue;
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

void count_ways()
{
    const int L=18;
    ways[pii(0LL,1LL)] = 1;
    for (int len=1; len<=L; ++len)
    for (int x=0; x<K; ++x)
    {
    int64 ans = 0;
    int64 val = vals[x];
    //printf("len %d val %lld\n", len, val);
    for (int d=1; d<=9; ++d) if (val % d == 0)
    {
        //ans += ways[pii(len-1,val/d)];  // map is slow
        ans &= M;
    }
    //ways[pii(len,val)] = ans;
    }
    /*
    for (int len=1; len <= L; ++len)
    {
    for (int x=0; x<K; ++x)
    {
        pii mykey = pii(len, vals[x]);
        if (x == 0) sums[mykey] = ways[mykey];
        else {
            int64 t = sums[pii(len, vals[x-1])] + ways[mykey];
            t &= M;
            sums[mykey] = t;
        }
    }
    }
    */
}


int main()
{
    init();
    count_ways();
}
