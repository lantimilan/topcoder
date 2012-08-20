// =========================================================
// 
//       Filename:  stringtrans.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/07/2012 04:40:20 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/07/2012, LI YAN
// 
// =========================================================
//
// keep getting WA, 0/10 passed, what is wrong?
//
// finally
//Submission Accepted
//10/10 testcases passed
//30 Point(s) 

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MOD=1000000000+7;

int N, K;

int prime[1000];
int nprime;
int comb[1005][1005];

char s[1005];
int pfactor[1000];
int nfactor;
int dp[1005][1005][4];

int add(int a, int b)
{
    return int(((long long)a + b)%MOD);
}

int sub(int a, int b)
{
    int c = a-b; if (c<0) c+=MOD;
    return c;
}

void gencomb()
{
    comb[0][0]=1;
    for(int i=1; i<=1000; ++i)
    {
        comb[i][0]=comb[i][i]=1;
        for(int j=1; j+j<=i; ++j)
        {
            comb[i][j] = comb[i][i-j] = add(comb[i-1][j], comb[i-1][j-1]);
        }
    }
//    for(int i=0; i<10; ++i)
//    {
//        for(int j=0; j<=i; ++j) printf("%d ", comb[i][j]);
//        putchar('\n');
//    }
}

void genprime()
{
    int isprime[1005];
    for(int i=0; i<1000; ++i) isprime[i]=1;

    nprime=0;
    for(int i=2; i<1000; ++i) if (isprime[i])
    {
        prime[nprime++]=i;
        for(int j=i+i; j<1000; j+=i) isprime[j]=0;
    }

    //for(int i=0; i<nprime; ++i) printf("%d ", prime[i]); putchar('\n');
}

void init()
{
    genprime();
    gencomb();
}

int calc(int p, int pos, int avail, int flag)
{
    if (pos==p) return (flag==3); // binary 11
    if (dp[pos][avail][flag]>=0) return dp[pos][avail][flag];

    int zero=0, one=0;
    for(int j=pos; j<N; j+=p) {
        zero += (s[j]=='0');
        one  += (s[j]=='1');
    }
    int ans=0;
    if (avail>=zero) { // flip all zero to 1
        ans = add(ans, calc(p, pos+1, avail-zero, flag|1<<1));
    }
    if (avail>=one) { // flip all one to 0
        ans = add(ans, calc(p, pos+1, avail-one, flag|1<<0));
    }
    return dp[pos][avail][flag]=ans;
}

void solve()
{
    scanf("%d%d ", &N, &K); 
    gets(s);
    //printf("\ntestcase\nN %d K %d\n", N, K); puts(s);

    if (N==1) {
        int ans=1;
        if (K==1) ++ans;
        printf("%d\n", ans);
        return;
    }

    nfactor=0;
    for(int i=0; i<nprime && prime[i]<N; ++i) {
        if (N%prime[i]==0) pfactor[nfactor++]=prime[i];
    }

    //for(int i=0; i<nfactor; ++i) printf("%d ", pfactor[i]); putchar('\n');

    int ans=0;
    int zero=0, one=0;
    for(int i=0; i<N; ++i) {
        zero += (s[i]=='0');
        one  += (s[i]=='1');
    }
    if (K >= zero) ans++;
    if (K >= one)  ans++;

    int periodcnt[1005]={0};
    vector<int> v;
    for(int p=2; p*p<=N; ++p) if (N%p==0) {
        v.push_back(p);
        if (N/p >p) v.push_back(N/p);
    }
    sort(v.begin(), v.end());
    
    for(int i=0; i<int(v.size()); ++i) {
        int period = v[i];
        int curr;
        memset(dp, -1, sizeof dp);    
        curr=calc(period, 0, K, 0);
        ans = add(ans, periodcnt[period]);
        for(int f=2; f<period; ++f) if(period % f==0) // can improve sqrt(period)
            curr = sub(curr, periodcnt[f]);
        periodcnt[period]=curr;
        ans = add(ans, curr);
        //printf("period %d dp %d\n", period, dp[0][K][0]);
    }
    int total = 0;
    for(int i=0; i<=K; ++i) 
        total = add(total, comb[N][i]);
    //printf("total %d\n", total);

    ans = sub(total, ans);
    printf("%d\n", ans);
}

int main()
{
    init();
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
