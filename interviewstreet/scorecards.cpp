// scorecards.cpp
//
// inserting -1 into seq of K with non-1
// let #-1 be L
//
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int64;

const int MOD=1000000000+7;
int s[45];
int dp[42][42][42]; // kth -1, pos, val

void refadd(int &a, int b)
{
    a = ((int64)a+b)%MOD;
}

// each tournament with N nodes has sum=N*(N-1)/2
void solve()
{
    int N, M, K, L; scanf("%d", &N);
    M=N*(N-1)/2;
    K=L=0;
    for(int i=0; i<N; ++i) {
        int d; scanf("%d", &d);
        if (d>=0) s[K++]=d;
        else L++;
    }

    sort(s, s+K);
    memset(dp, 0, sizeof dp);
    dp[0][0][0]=1;
    for(int i=1; i<=L; ++i)
    for(int prev=0; prev<=K; ++prev)
    for(int pos=prev; pos<=K; ++pos) 
    for(int pval=0; pval<N; ++pval)
    for(int val=pval; val<N; ++val)
    {
        refadd(dp[i][pos][val], dp[i-1][prev][pval]);
    }
    int ans=0;
    for(int p=0; p<=K; ++p)
    for(int v=0; v<N; ++v)
    {
        printf("dp %d\n", dp[L][p][v]);
        refadd(ans, dp[L][p][v]);
    }
    printf("%d\n", ans);
}
int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}

// WA: because each subset must have inner total score = (k choose 2)
// and after max=N-1 is taken, the next max is N-2
//
// Landau's theorem
// s1,s2,...,sn is a score sequence iff
// s1<=s2<=...<=sn
// sum_i=1^k s_i >= (k choose 2)
// sum_i=1^n s_i = (n choose 2)
