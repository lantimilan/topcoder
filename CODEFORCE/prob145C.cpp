// p145C.cpp
//
#include <cassert>
#include <cstdio>
#include <map>
using namespace std;

const int MOD=1000000000+7;
int a[100000+5];
int fact[100000+5];
int dp[1024][1024]; // only L different lucky, L=1022
map<int,int> cnt;
int lucky[1024];
int L;


void add(int &a, int b)
{
    a = ((long long)a+b) %MOD;
}

int mult(int a, int b)
{
    return (long long)a*b % MOD;
}
void init()
{
    L=0;
    for(int d=1; d<10; ++d) {
        for(int b=0; b<(1<<d); ++b) {
            int k=0, f=1;
            for(int p=0; p<d; ++p, f*=10) {
                if (1<<p & b) k+=7*f;
                else k+=4*f;
            }
            lucky[L++]=k;
        }
    }
    //printf("L=%d\n", L);
    fact[0]=fact[1]=1;
    for(int i=2; i<=100000; ++i) {
        fact[i]=mult(i, fact[i-1]);
    }
}

//int translate(int n)
//{
    //int s=n;
    //int ans=0, p=0;
    //while(n) {
        //if (n%10==4) {}
        //else if (n%10==7) { ans|=1<<p; }
        //else return -1;
        //++p; n/=10;
    //}
    //printf("translate %d to %d\n", s, ans);
    //return ans;
//}

int fastpow(int a, int b)
{
    int ans=1, f=a;
    while(b) {
        if (b&1) ans = mult(ans, f);
        f = mult(f, f);
        b>>=1;
    }
    return ans;
}

int inv(int a)
{
    return fastpow(a, MOD-2);
}

int choose(int n, int k)
{    
    if (n<k) return 0;
    //if (k>n/2) return choose(n,n-k);
    //int ans=1, deno=1;
    //for(int i=n; i>n-k; --i) ans=mult(ans, i);
    //for(int i=k; i>1; --i) deno=mult(deno, i);
    int deno=mult(fact[k], fact[n-k]);
    int ans=mult(fact[n], inv(deno));
    return ans;
}

bool islucky(int n)
{
    while(n) {
        if (n%10==4) {}
        else if (n%10==7) {}
        else return false;
        n/=10;
    }
    return true;
}

int main()
{    
    int N, K; scanf("%d %d", &N, &K);
    for(int i=0; i<N; ++i) scanf("%d", &a[i]);
    
    init();
    
    int other=0;
    for(int i=0; i<N; ++i) {
        if (islucky(a[i])) cnt[a[i]]++;        
        else other++;
    }
        
    dp[0][0]=1;
    for(int i=0; i<L; ++i) {
        for(int k=0; k<=i; ++k) {
            add(dp[i+1][k+1], mult(dp[i][k], cnt[lucky[i]]));
            add(dp[i+1][k], dp[i][k]);
        }
    }
        
    int ans=0;
    for(int k=0; k<=L; ++k) {
        if (K-k>=0)
            add(ans, mult(dp[L][k], choose(other, K-k)));
    }
    printf("%d\n", ans);
}

//1129852 	Feb 1, 2012 11:07:27 AM 	lantimilan 	C - Lucky Subsequence 	GNU C++ 	Accepted 	110 ms 	6300 KB
// wrong fact[] because mult() is used incorrectly
//1129848 	Feb 1, 2012 11:05:20 AM 	lantimilan 	C - Lucky Subsequence 	GNU C++ 	Wrong answer on test 1 	50 ms 	6300 KB
// forgot to precompute fact[]
//1129837 	Feb 1, 2012 10:58:53 AM 	lantimilan 	C - Lucky Subsequence 	GNU C++ 	Time limit exceeded on test 23 	2000 ms 	5900 KB
//1129833 	Feb 1, 2012 10:55:55 AM 	lantimilan 	C - Lucky Subsequence 	GNU C++ 	Time limit exceeded on test 23 	2000 ms 	5900 KB
// wrong count on 4,7 lucky
//1129802 	Feb 1, 2012 10:21:51 AM 	lantimilan 	C - Lucky Subsequence 	GNU C++ 	Wrong answer on test 7 	30 ms 	5800 KB 
