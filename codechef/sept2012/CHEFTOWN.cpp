// =========================================================
// 
//       Filename:  CHEFTOWN.cpp
// 
//    Description:  http://www.codechef.com/SEP12/problems/CHEFTOWN
// 
//        Version:  1.0
//        Created:  09/01/2012 09:50:26 PM
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
#include <deque>
using namespace std;

typedef pair<int,int> pii;
int vals[400000+5];

deque<pii> minque; // val, pos
deque<pii> maxque; // val, pos

int main()
{
    int N, W; scanf("%d%d", &N, &W);
    for(int i=0; i<N; ++i) {
        scanf("%d", vals + i);
    }

    int ans=0;
    if (W==1) { printf("%d\n", N); return 0; }

    minque.push_back(pii(vals[0], 0));
    maxque.push_back(pii(vals[0], 0));
    for(int i=1; i<N; ++i) {
        if (minque.front().second <= i-W) minque.pop_front();
        if (maxque.front().second <= i-W) maxque.pop_front();
        while(!minque.empty() && vals[i] <= minque.back().first) {
            minque.pop_back();
        }
        minque.push_back(pii(vals[i], i));
        while(!maxque.empty() && vals[i] >= maxque.back().first) {
            maxque.pop_back();
        }
        maxque.push_back(pii(vals[i], i));
        if (i>=W-1) {
            int mm, xx;
            mm = minque.front().first;
            xx = maxque.front().first; //printf("%d %d\n", mm, xx);
            if (xx - mm == W-1) ans++;
        }
    }
    printf("%d\n", ans);
}

// Correct Answer
// Execution Time: 6.75
// slide window min and max
// logn stl set is too slow
