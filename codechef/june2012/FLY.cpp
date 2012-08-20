// =========================================================
// 
//       Filename:  FLY.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/03/2012 10:48:55 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/03/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

bool match(int u[][2])
{
    if (u[0][0]==u[1][0]) return true;
    if (u[0][0]==u[1][1]) return true;
    if (u[0][1]==u[1][0]) return true;
    if (u[0][1]==u[1][1]) return true;
    return false;
}

void solve()
{
    int N, M;
    double C;
    scanf("%d%lf%d", &N, &C, &M);
    int u[2][2];
    for(int i=0; i<M; ++i)
        scanf("%d%d", &u[i][0], &u[i][1]);

    double ans=0;
    if (C<=2) { // use clique
        ans = 1.0*N*(N-1) + C*(1.0*N*(N-1)/2 - M);
    }
    else {
        if (M<=1 || (M==2 && match(u))) { // star
            ans = 2.0*N*(N-1) - 2*1.0*(N-1) + (N-1 - M)*C;
        }
        else {
            ans = (1.0*(N-2) + 2.0*1);
            ans += 2.0*(N-2)*(N-3) + 1.0*(N-2) + 1.0*1 + 3.0*(N-3);
            ans += (1.0+2.0+3.0*(N-3));
            ans += (N-1-M)*C;

            //printf("ans %lf\n", ans);
            if (C<2.0*(N-2)) ans -= (2.0*(N-2)-C);
            //printf("ans %lf\n", ans);
        }
    }
    printf("%.13f\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--) solve();
}
