// =========================================================
// 
//       Filename:  HORSES.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/01/2012 08:17:48 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/01/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
using namespace std;

int S[5005];

void solve()
{
    int N; scanf("%d", &N);

    for(int i=0; i<N; ++i)
        scanf("%d", S+i);
    sort(S, S+N);
    int d = S[1] - S[0];
    for(int i=2; i<N; ++i)
        d = min(d, S[i] - S[i-1]);
    printf("%d\n", d);
}
int main()
{
    int T; scanf("%d", &T);
    for(int i=0; i<T; ++i)
        solve();
}
