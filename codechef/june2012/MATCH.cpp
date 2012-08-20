// =========================================================
// 
//       Filename:  MATCH.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/10/2012 05:26:05 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/10/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int N, M;
double P[6][105];

void solve()
{
    double ans=0.0;
    int match;
    // 1 match
    match=1;
    // only one of M right vertex connects
    for(int j=0; j<M; ++j) {
        double prob=1.0;
        // j connects to at least one of N left vertex
        double sub=1.0;
        for(int i=0; i<N; ++i) sub *= (1-P[i][j]);
        prob -= sub;
        // none of the M-1 right connects
        for(int k=0; k<M; ++k) if (k!=j) {
            for(int i=0; i<N; ++i) prob *= (1-P[i][k]);
        }
    }
    ans += match * prob;

    // 2 match
    match=2;


}
int main()
{
    scanf("%d%d", &N, &M);   
    for(int i=0; i<N; ++i)
    for(int j=0; j<M; ++j)
        scanf("%lf", &P[i][j]);

    solve();
}
