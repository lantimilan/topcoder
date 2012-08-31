// =========================================================
// 
//       Filename:  prob104E.cpp
// 
//    Description:  http://codeforces.com/contest/104/problem/E
// 
//        Version:  1.0
//        Created:  08/09/2011 12:23:21 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/09/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define sz(a) int(a.size())

typedef long long LL;

LL sum[300000+5];
int cows[300000+5];
LL ans[300000+5];
pair<pair<int,int>,int> vec[300000+5];

void calc(int b, int n)
{
    for(int a=n; a>=1; --a)
        if (a+b<=n) sum[a] = sum[a+b] + cows[a-1];
        else sum[a] = cows[a-1];
}

void solve()
{
    int n; scanf("%d",&n);
    for(int i=0; i<n; ++i) scanf("%d",&cows[i]);
    int p; scanf("%d",&p);

    for(int i=0; i<p; ++i)
    {
        int a,b; scanf("%d%d", &a,&b);
        vec[i].first=pair<int,int>(b,a);
        vec[i].second=i;
    }

    sort(vec,vec+p);
    const int TH=500;
    int b0=-1;
    int i;
    for(i=0; i<p; ++i)
    {
        int a,b; b=vec[i].first.first; a=vec[i].first.second;
        int idx=vec[i].second;
        if (b>=TH) break; 
        if (b!=b0) { calc(b,n); b0=b; }
        ans[idx]=sum[a];
    }
    // naive calc
    for(; i<p; ++i)
    {
        int a,b; b=vec[i].first.first; a=vec[i].first.second;
        int idx=vec[i].second;
        LL res=0LL; // use local to reduce access to array
        for(int k=a; k<=n; k+=b) res += cows[k-1];
        ans[idx] = res;
    }

    for(int i=0; i<p; ++i)
    {
        printf("%lld\n", ans[i]);
    }
}

int main()
{
    solve();
}

// change cin/cout to scanf/printf speed up from 1970ms to 890ms
// 601114   Aug 10, 2011 12:39:49 AM    lantimilan  E - Time to Raid Cowavans
// GNU C++  Accepted    890 ms  10800 KB 
//
// 601112   Aug 10, 2011 12:36:55 AM    lantimilan  E - Time to Raid Cowavans
// GNU C++  Accepted    1970 ms     10800 KB 
// a stupid bug: should be b0=b, but I wrote b=b0
//
// repeated push_back for 3x10^5 times maybe the cause of TLE
// still TLE
//
// OK, even vector might be too expensive, use array
// seems map is too slow. No, something else is wrong.
// 601023   Aug 9, 2011 10:56:03 PM     lantimilan  E - Time to Raid Cowavans
// GNU C++  Time limit exceeded on test 9   4000 ms     11600 KB 
