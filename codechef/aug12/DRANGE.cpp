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
#include <climits>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;
 
typedef pair<int,int> pii;
 
#define MAX 10005
pii left[MAX], right[MAX];
int N, M;

void chmin(int &a, int b)
{
    a = (a<b)?a:b;
}

void chmax(int &a, int b)
{
    a = (a>b)?a:b;
}

int main()
{
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &N, &M);
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

        int vmin=INT_MAX, vmax=INT_MIN;
        int sum;
        int xl, xr;
        sum = 0;
        xl=xr=0;
        for(int p=0; p<N; ++p) {
            for(; xl<M && left[xl].first<=p; xl++) sum += left[xl].second;
            for(; xr<M && right[xr].first<p; xr++) sum -= right[xr].second;
            int val = 1+p+sum;
            chmin(vmin, val);
            chmax(vmax, val);
        }
        printf("%d\n", vmax - vmin);
    }
}

// AC
// Correct Answer
// Execution Time: 4.17
// TLE
