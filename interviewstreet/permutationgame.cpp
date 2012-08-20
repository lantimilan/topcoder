// =========================================================
// 
//       Filename:  permutationgame.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/03/2012 04:13:40 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/03/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <map>
using namespace std;

map<int, bool> dp;
int N;
int a[20];

bool win(int mask, int turn)
{
    if (dp.count(mask)) return dp[mask];
    bool isincr=true;
    int k=0;
    for(int i=0; i<N; ++i) if (mask & 1<<i) {
        if (a[i]>k) { k=a[i]; }
        else { isincr=false; }
    }
    if (isincr) return false;

    for(int i=0; i<N; ++i) if (mask & 1<<i) {
        if (!win(mask^(1<<i), 1-turn)) 
            return dp[mask]=true;
    }
    return dp[mask]=false;
}
void solve()
{
    dp.clear();
    scanf("%d", &N);
    for(int i=0; i<N; ++i) scanf("%d", &a[i]);

    int ans=win((1<<N)-1, 0);
    if (ans) puts("Alice");
    else puts("Bob");
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
