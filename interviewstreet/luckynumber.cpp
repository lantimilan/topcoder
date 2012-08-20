// lucky numbers
//
// actually no, just recursion without memorization
// seems the subcases have very little overlap and set up map for memorization is too expensive
// use memorization since there are a lot of invalid states
//

#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

const int MAX=140;
long long all[20][140][140];
long long small[20][140][140];
long long partial[20][10][140][140]; // pos, digit, sum, sqr
int table[]={ 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139, };
int sumtable[][10]= {
{2,-1,},
{3,-1,},
{3,5,-1,},
{5,7,-1,},
{5,7,11,-1,},
{5,7,11,13,-1,},
{5,7,11,13,17,-1,},
{7,11,13,17,-1,},
{11,13,17,19,-1,},
{7,11,13,17,19,-1,},
{11,13,17,19,-1,},
{7,11,13,17,19,23,-1,},
{11,13,17,19,23,-1,},
{11,13,17,19,23,-1,},
{11,13,17,19,23,-1,},
{11,13,17,19,23,29,-1,},
{11,13,17,19,23,29,31,-1,},
{11,13,17,19,23,29,31,-1,},
{11,13,17,19,23,29,31,-1,},
{13,17,19,23,29,31,-1,},
{11,13,17,19,23,29,31,-1,},
{17,19,23,29,31,37,-1,},
{11,17,19,23,29,31,37,-1,},
{13,17,19,23,29,31,37,-1,},
{13,17,19,23,29,31,37,41,-1,},
{17,19,23,29,31,37,41,-1,},
{17,19,23,29,31,37,41,-1,},
{17,19,23,29,31,37,41,43,-1,},
{17,19,23,29,31,37,41,43,-1,},
{17,19,23,29,31,37,41,43,-1,},
{19,23,29,31,37,41,43,47,-1,},
{17,19,23,29,31,37,41,43,47,-1,},
{19,23,29,31,37,41,43,47,-1,},
{19,23,29,31,37,41,43,47,-1,},
};
int N;

typedef pair<int,int> pii;
typedef pair<int,pii> triple_t;
map<triple_t, long long> memo;

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

long long recurse(int pos, int digits[], int sum, int sqr)
{
    //if (sum > sqr) return 0;
    if (pos==0) {
        return sum==0 && sqr==0;
    }
    int d=digits[pos-1];
    //triple_t curr; curr.first=pos; curr.second=pii(sum, sqr);
    //if (memo.count(curr)) return memo[curr];
    //long long &ans=memo[curr];
    long long ans=partial[pos][d][sum][sqr];
    if (sum>=d && sqr>=d*d && sum-d <= sqr-d*d)
        ans += recurse(pos-1, digits, sum-d, sqr-d*d);
    return ans;
}

long long calc(long long lim)
{
//printf("calc %lld ", lim);
    int limit[20]={0};
    int n;
    for(n=0; lim; lim/=10, ++n) {
        limit[n]=lim%10;
    }
    long long ans=0;

    //memo.clear();
    // for a fixed sqr, only <10 sums are possible
    // and maxsum=47
    // see luckypart.cpp
    // store in sumtable[][]
    // 
    //for(int xs=0; xs<N && table[xs]<=47; ++xs)
    //for(int xq=0; xq<N; ++xq)
    //    ans+=recurse(n, limit, table[xs], table[xq]);
    for(int xq=0; xq<N; ++xq) {
    for(int xs=0; sumtable[xq][xs]>0; ++xs) {
        //printf("sum %d sqr %d\n", sumtable[xq][xs], table[xq]);
        ans+=recurse(n, limit, sumtable[xq][xs], table[xq]);
    }
    }
    return ans;
/*
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
    for(int xs=0; xs<N && table[xs]<=47; ++xs)
    for(int xq=xs; xq<N; ++xq)
        ans+=small[n][table[xs]][table[xq]];
//printf("%lld\n", ans);
    return ans;
    */
}

void solve()
{
    long long A, B; // 1<=A,B<=10^18 
    scanf("%lld%lld", &A, &B); 
    if (A==(long long)1.0e18) --A;
    if (B==(long long)1.0e18) --B;
    long long a = calc(A-1);
    long long b = calc(B);
    //printf("A %lld %lld B %lld %lld\n", A, a, B, b);
    printf("%lld: %lld\n", B, b-a);
    //printf("%lld\n", b-a);
}

int main()
{
    init();
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
