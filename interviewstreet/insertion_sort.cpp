// =========================================================
// 
//       Filename:  insertion_sort.cpp
// 
//    Description:  count number of inv
// 
//        Version:  1.0
//        Created:  06/15/2012 09:54:40 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/15/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
using namespace std;

int N;
int a[100000+5];

long long cntinv(int l, int r)
{
    if (l+1==r) return 0;
    long long ans=0;
    int m=(l+r)/2;
    ans += cntinv(l, m);
    ans += cntinv(m, r);
    sort(a+l, a+m);
    sort(a+m, a+r);
    int i, j;
    for(i=l, j=m; i<m && j<r; ) {
        if (a[i] <= a[j]) i++;
        else { ans+=m-i; j++; }
    }
    return ans;
}

void solve()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) scanf("%d", a+i);

    long long ans;
    ans = cntinv(0,N);
    printf("%lld\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--) solve();
}

// #    Status  Signal  Time
// 1    Passed  Success     0.111854
// 2    Passed  Success     0.121515
// 3    Passed  Success     0.121591
// 4    Passed  Success     0.111545
// 5    Passed  Success     0.394645
// 6    Passed  Success     0.242937
// 7    Passed  Success     0.233028
// 8    Passed  Success     0.457851
// 9    Passed  Success     0.546781
// 10   Passed  Success     0.394814
//
