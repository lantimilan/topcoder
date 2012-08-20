// =========================================================
// 
//       Filename:  median.cpp
// 
//    Description:  Little Elephant and Median
//
//    Problem code: MEDIAN
// 
//        Version:  1.0
//        Created:  05/03/2012 08:55:36 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/03/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;

map<int, int> dist;
void solve()
{
    int n; scanf("%d", &n);
    int a[40];
    for(int i=0; i<n; ++i) scanf("%d", a+i);

    int maxval=a[0];
    for(int i=1; i<n; ++i) maxval=max(maxval, a[i]);
    for(int i=0; i<n; ++i) if (a[i]==maxval) a[i]=1; else a[i]=0;

    int start=0;
    for(int i=0; i<n; ++i) start |= a[i]<<i;
    queue<int> que;
    que.push(start); dist[start]=0;
    while(!que.empty()) {
        start = que.front(); que.pop();
        assert(dist.count(start));
        int cnt1, cnt2, last;
        // the is O(n^2) to compute interval for each pos
        // TLE here
        for(int pos=0; pos<n; ++pos) {
            cnt1=cnt2=0; last=-1;
            for(int end=pos; end<n; ++end) {
                cnt2++; if (1<<end & start) cnt1++;
                if (2*cnt1>=cnt2) { last=end; }
            }
            if (last>=0) {
                int next = start;
                int cnt = last-pos+1;
                next |= ((1<<cnt)-1)<<pos;
                if (!dist.count(next)) {
                    dist[next]=dist[start]+1;
                    que.push(next);
                    if (next==(1<<n)-1) break;
                }
            }
        }
    }
    printf("%d\n", dist[(1<<n)-1]);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=1; t<=T; ++t) solve();
}
