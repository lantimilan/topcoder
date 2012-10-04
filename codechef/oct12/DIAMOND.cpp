// =========================================================
// 
//       Filename:  DIAMOND.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/02/2012 11:20:32 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/02/2012, LI YAN
// 
// =========================================================

// Let f(a,b) be expected gain with [a,b]
// then a simple DP is
// f(ab) = p(HH)  f(a+2,b) + v[a]
//         p(HT)  f(a+1,b-1) + v[a]
//         p(TH)  f(a+1,b-1) + v[b]
//         p(TT)  f(a,b-2) + v[b]
// However for T=500 and N=2000, this one will TLE
//
// linearity of expectation
// looks for N>=3
// second player takes left and right with p=1/4
// and inner ones with p=1/2

#include <cstdio>
using namespace std;

int V[2005];

int main()
{
    int T; scanf("%d", &T);
    while(T--) {
        int N; scanf("%d", &N);
        int sum=0;
        for(int i=0; i<N; ++i) {
            scanf("%d", V+i);
            sum += V[i];
        }
        double ans=0;
        if (N==1) {
            ans = sum;
        } else if (N==2) {
            ans = sum/2.0;
        } else if (N&1) {
            ans = sum/2.0 - (V[0]+V[N-1])/4.0;
            ans = sum-ans;
        } else {
            ans = sum/2.0;
        }
        printf("%.3f\n", ans);
    }
}

// WA
