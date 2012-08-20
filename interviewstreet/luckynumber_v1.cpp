// lucky numbers

#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const int MAX=140;
map<long long, long long> memo;
long long all[20][140][140];
long long small[20][140][140];
long long partial[20][10][140][140]; // pos, digit, sum, sqr
int table[]={ 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139, };
int N;

void init()
{
    N=sizeof(table)/sizeof(int);
    // only primes <=139 can be represented by sum of 18 digits
    // see luckyhelp.cpp
    memset(all, 0, sizeof all); 
    all[0][0][0]=1;
    for(int pos=0; pos<18; ++pos)
    for(int d=0; d<10; ++d)
    for(int sum=0; sum+d<MAX; ++sum)
    for(int sqr=sum; sqr+d*d<MAX; ++sqr)
    {
        all[pos+1][sum+d][sqr+d*d]+=all[pos][sum][sqr];
    }
    for(int pos=0; pos<18; ++pos)
    for(int d=0; d<10; ++d)
    for(int dd=d+1; dd<10; ++dd)
    for(int sum=0; sum+d<MAX; ++sum)
    for(int sqr=sum; sqr+d*d<MAX; ++sqr)
    {
        partial[pos+1][dd][sum+d][sqr+d*d]+=all[pos][sum][sqr];
    }
}

long long calc(long long lim)
{
    if (memo.count(lim)) return memo[lim];
//printf("calc %lld ", lim);
    int limit[20]={0};
    int n;
    for(n=0; lim; lim/=10, ++n) {
        limit[n]=lim%10;
    }

    long long ans=0;
    //memset(small, 0, sizeof small);
    small[0][0][0]=1;
    for(int pos=0; pos<n; ++pos)
    //for(int d=0; d<10; ++d)
    for(int sum=0; sum<=47; ++sum)
    for(int sqr=sum; sqr<MAX; ++sqr)
    {
        int d=limit[pos];
        small[pos+1][sum][sqr]=partial[pos+1][d][sum][sqr];
        if (sum>=d && sqr>=d*d)
            small[pos+1][sum][sqr]+=small[pos][sum-d][sqr-d*d];
    }
    for(int xs=0; xs<N; ++xs)
    for(int xq=xs; xq<N; ++xq)
        ans+=small[n][table[xs]][table[xq]];
//printf("%lld\n", ans);
    return memo[lim]=ans;
}

void solve()
{
    long long A, B; // 1<=A,B<=10^18 
    scanf("%lld%lld", &A, &B); 
    if (A==(long long)1.0e18) --A;
    if (B==(long long)1.0e18) --B;
    long long a = calc(A-1);
    long long b = calc(B);
    printf("A %lld %lld, B %lld %lld\n", A, a, B, b);
    printf("%lld\n", b-a);
}

int main()
{
    init();
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
