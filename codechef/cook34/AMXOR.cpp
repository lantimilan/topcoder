// =========================================================
// 
//       Filename:  AMXOR.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/19/2013 10:22:53 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/19/2013, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
using namespace std;

int a[100000+5];

void solve()
{
    int N; scanf("%d", &N);
    for (int i = 0; i < N; ++i) scanf("%d", a+i);
    sort(a, a+N);

    int sum = 0;
    for (int i = 0; i < N; ++i) sum ^= a[i];
}

int main()
{
    int T; scanf("%d", &T);
    while (T--)
        solve();
}
