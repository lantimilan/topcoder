// =========================================================
// 
//       Filename:  DRANGE.cpp
// 
//    Description:  http://www.codechef.com/AUG12/problems/DRANGE
// 
//        Version:  1.0
//        Created:  08/03/2012 09:50:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/03/2012, LI YAN
// 
// =========================================================

// segment tree
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;
 
typedef pair<int,int> pii;
 
#define MAX (1<<20)
pii left[MAX], right[MAX];
int val[MAX];
int N, M;

int main()
{
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &N, &M);
        for(int i=0; i<N; ++i) {
            val[i] = i+1;
        }
        for(int i=0; i<M; ++i) {
            int w, x, y, z;
            scanf("%d%d%d%d", &w, &x, &y, &z);
            if (w==2) z = -z;
            --x; --y;
            left[i] = pii(x, z);
            right[i] = pii(y, z);
        }
        sort(left, left+M);
        sort(right, right+M);

        int sum;
        int xl, xr;
        sum = 0;
        xl=xr=0;
        for(int p=0; p<N; ++p) {
            for(; xl<M && left[xl].first<=p; xl++) sum += left[xl].second;
            for(; xr<M && right[xr].first<p; xr++) sum -= right[xr].second;
            val[p] += sum;
        }
        int vmin=val[0], vmax=val[0];
        for(int p=0; p<N; ++p) {
            vmin=min(vmin, val[p]);
            vmax=max(vmax, val[p]);
        }
        printf("%d\n", vmax - vmin);
    }
}

// TLE
