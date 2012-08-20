// =========================================================
// 
//       Filename:  gridwalk.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/10/2012 12:51:20 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/10/2012, LI YAN
// 
// =========================================================

// Finally got AC
// it is not hard but I made too many mistakes
//
// Mon Feb  6 10:12:07 PST 2012
// dp with precalculation on one dim
//
// each dim is independent and almost identical
// so can partition M=300 into 10 parts, 
// each partition can be solved quickly by caching each dim
//
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

//int mymove[105][105][305]; // (size, start, mymove) of one dimension
int tmp[105][305]; // (pos, mymove)
int dp[105][305]; // dim, mymove
int choose[305][305]; // totalmove, currmove

typedef pair<int,int> pii;
typedef pair<pii,int> tri;
map<tri,int> mymove;

const int MOD=1000000007;

void refadd(int &a, int b)
{
    a = ((long long)a + b) % MOD;
}

int mult(int a, int b)
{
    return (long long)a*b % MOD;
}

// a^b
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

void init()
{
    choose[0][0]=1;
    for(int m=1; m<=300; ++m) {
        choose[m][0]=1;
        for(int c=1; c<=m; ++c)
        {
            refadd(choose[m][c], choose[m-1][c]);
            refadd(choose[m][c], choose[m-1][c-1]);
        }
    }
}

void calc(int dim, int start)
{
        if (mymove.count(tri(pii(dim,start),1))) return;
        mymove[tri(pii(dim,start),0)]=1;
        memset(tmp, 0, sizeof tmp);
        tmp[start][0]=1;
        for(int m=1; m<=300; ++m) {
            for(int p=1; p<=dim; ++p) {
                if (p-1>=1) refadd(tmp[p-1][m], tmp[p][m-1]);
                if (p+1<=dim) refadd(tmp[p+1][m], tmp[p][m-1]);
            }
            for(int p=1; p<=dim; ++p) {
                refadd(mymove[tri(pii(dim,start),m)], tmp[p][m]);
            }
        }
}

void solve()
{
    int N, M; scanf("%d%d", &N, &M); //printf("N %d M %d\n", N, M);
    int D[20], x[20];
    for(int i=0; i<N; ++i) scanf("%d", &x[i]);
    for(int i=0; i<N; ++i) scanf("%d", &D[i]); 

    for(int i=0; i<N; ++i) {
        calc(D[i], x[i]);
    }

    memset(dp, 0, sizeof dp);
    for(int i=0; i<N; ++i) {
        dp[i][0]=1;
        for(int m=0; m<=M; ++m) if (dp[i][m]>0) {
            for(int c=0; c+m<=M; ++c) {
                int mm=mymove[tri(pii(D[i],x[i]),c)];
                int t = choose[c+m][c];
                t = mult(t, dp[i][m]);
                t = mult(t, mm);
                refadd(dp[i+1][c+m], t);
            }
        }
    }
    printf("%d\n", dp[N][M]);
}

int main()
{
    int T; scanf("%d", &T);
    init();
    for(int t=1; t<=T; ++t)
        solve();
}

// a cleaner version, handles edge case m=0,c=0 better
// Grid Walking     C++     
// Submission Accepted
// 11/11 testcases passed
// 50 Point(s)
//  View Submission     Processed   2012-02-06 18:15 UTC
//
// Grid Walking     C++     
// Submission Accepted
// 11/11 testcases passed
// 50 Point(s)
//  View Submission     Processed   2012-02-06 18:03 UTC
//
// Grid Walking     C++     
// Wrong Answer: did not check whether mymove(dim, start, m) has been computed
// 6/11 testcases passed
// 28 Point(s)  View Submission     Processed   2012-02-06 17:50 UTC
// Wrong Answer: did not handle m=0 or c=0 properly
// 2/11 testcases passed
// 4 Point(s)   View Submission     Processed   2012-02-06 17:39 UTC
// Grid Walking     C++     
// Wrong Answer
// 1/11 testcases passed
// 1 Point(s)   View Submission     Processed   2012-02-06 17:00 UTC
// Grid Walking     C++     
// Time Limit Exceeded: try to compute all dim<=100, start<=100 when need only
// 10 pairs of them
// 1/11 testcases passed
// 1 Point(s)   View Submission     Processed   2012-02-06 16:48 UTC
// Grid Walking     C++     
// Wrong Answer
// 1/11 testcases passed
// 1 Point(s)   View Submission     Processed   2012-02-06 08:08 UTC
// Grid Walking     C++     
// Compilation failed
// All testcases failed
// 0 Point(s)   View Submission     Processed   2012-02-06 08:04 UTC
// Grid Walking     C++     
// Time Limit Exceeded
// All testcases failed
// 0 Point(s)   View Submission     Processed   2012-02-06 07:53 UTC
