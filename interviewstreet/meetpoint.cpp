// =========================================================
// 
//       Filename:  meetpoint.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/16/2012 09:17:12 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/16/2012, LI YAN
// 
// =========================================================

// Meeting Point    C++     
// Submission Accepted
// 13/13 testcases passed
// 50 Point(s)
//  View Submission     Processed   2012-01-21 23:33 UTC
//  Meeting Point   C++     
//  Wrong Answer
//  4/13 testcases passed
//  8 Point(s)  View Submission     Processed   2012-01-21 23:22 UTC
//
// the L_inf metric max{|x2-x1|, |y2-y1|}
// is equivalent to L_1 metric with (x,y) rotated 45deg
// with proper scaling
//
#include <algorithm>
#include <cstdio>
#include <utility>
using namespace std;

typedef pair<long long,int> pii; // coord, pos

#define MAXN 100005
int x[MAXN], y[MAXN];
pii px[MAXN], py[MAXN];
long long dx[MAXN], dy[MAXN];
long long dist[MAXN];

template<class T>
void chmin(T &a, const T &b)
{ if (a>b) a=b; }

int main()
{
    int N; scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        px[i].first=x[i]+y[i], px[i].second=i;
        py[i].first=x[i]-y[i], py[i].second=i;
    }
    sort(px, px+N);
    sort(py, py+N);
    for(int i=1; i<N; ++i) {
        dx[0]+=px[i].first-px[0].first;
        dy[0]+=py[i].first-py[0].first;
    }
    for(int i=1; i<N; ++i) {
        dx[i]=dx[i-1]-(N-i-i)*(px[i].first-px[i-1].first);
        dy[i]=dy[i-1]-(N-i-i)*(py[i].first-py[i-1].first);
    }
    for(int i=0; i<N; ++i) {
        dist[px[i].second] += dx[i];
        dist[py[i].second] += dy[i];
    }
    long long best=dist[0];
    for(int i=1; i<N; ++i) chmin(best, dist[i]);
    printf("%lld\n", best/2);
}
