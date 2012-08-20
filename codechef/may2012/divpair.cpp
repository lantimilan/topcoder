// =========================================================
// 
//       Filename:  divpair.cpp
// 
//    Description:  Divisible Pairs
//
//    Problem code: DIVPAIR
// 
//        Version:  1.0
//        Created:  05/03/2012 10:54:39 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/03/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

typedef long long int64;

int64 sum(int64 a, int64 b, int64 d)
{
    return (a+b)*((b-a)/d+1)/2;
}

int64 solve(int N, int M)
{
    //int N, M; scanf("%d%d", &N, &M);
    int64 mid = (N+1)/M;
    int64 cap = (2*N-1)/M;
    int64 ans=0;
    int64 odd1, odd2, even1, even2, first, last;
    //printf("N %d M %d mid %lld cap %lld\n", N, M, mid, cap);
    if (M%2==0) {
        first = M-M/2-1; last = mid*M-mid*M/2-1;
        if (1<=mid)
            ans += sum(first, last, M/2);
        first = N-(mid+1)*M/2; last = N-cap*M/2;
        if (mid+1<=cap)
            ans += sum(first, last, -M/2);
    }
    else {
        odd1 = (mid&1) ? mid : mid-1;
        even1 = (mid&1) ? mid-1 : mid;
        first = M-(M/2+1); last = odd1*M-(odd1*M/2+1);
        if (1<=odd1)
            ans += sum(first, last, M);

        first = 2*M - (2*M/2+1); last = even1*M - (even1*M/2+1);
        if (2<=even1)
            ans += sum(first, last, M);

        odd1+=2; even1+=2;
        odd2=(cap&1)?cap:cap-1;
        even2=(cap&1)?cap-1:cap;

        first = N-odd1*M/2; last = N-odd2*M/2;
        if (odd1<=odd2)
            ans += sum(first, last, -M);

        first = N-even1*M/2; last = N-even2*M/2;
        if (even1<=even2)
            ans += sum(first, last, -M);
    }
    //printf("%lld\n", ans);
    return ans;
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=1; t<=T; ++t) {
        int N, M; scanf("%d%d", &N, &M);
        int64 ans = solve(N, M);
        printf("%lld\n", ans);
    }
    /*
    for(int N=1; N<100; ++N)
    for(int M=2; M<100; ++M)
    {
        //printf("N %d M %d\n", N, M);
        int64 cnt=0, my=0;
        for(int a=1; a<=N; ++a)
        for(int b=a+1; b<=N; ++b)
            if ((a+b)%M==0) ++cnt;
        my = solve(N, M);
        if (cnt != my) {
            puts("BAD");
            //printf("N %d M %d ans %lld my %lld\n", N, M, cnt, my);
            return 1;
        }
        else {
            //puts("PASS");
        }
    }
    */
}

// Accepted
// 1014976  47 sec ago  Divisible Pairs     
//    0.48    2.6M    C++ 4.3.2   View Solution 
// 1014543     4 hours ago     Divisible Pairs     
//    0.48    2.6M    C++ 4.3.2   View Solution 
// 1014535     4 hours ago     Divisible Pairs     
//    0.47    2.6M    C++ 4.3.2   View Solution
