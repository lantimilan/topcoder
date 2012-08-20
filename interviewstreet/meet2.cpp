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

#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 100005
int x[MAXN], y[MAXN];

int main()
{
    int N; scanf("%d", &N);
    for(int i=0; i<N; ++i)
        scanf("%d%d", &x[i], &y[i]);

    long long best=(long long)1.0e16;
    int id=0;
    for(int i=0; i<N; ++i) {
        long long curr=0;
        for(int j=0; j<N; ++j) {
            curr += max(abs(x[i]-x[j]), abs(y[i]-y[j]));
        }
        //best = min(best, curr);
        if (curr<best) { id=i; best=curr; }
    }
    printf("%d %lld\n", id, best);
}
