// =========================================================
// 
//       Filename:  prob148E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/05/2012 10:25:36 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 02/05/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

int a[105][105];
int c[105];
int dp[105][105]; // (row, cnt) max val to take cnt items from row
int total[105][10000+5]; // (row+1, cnt) max val to take total of cnt items with last at row

void chmax(int &a, int b)
{
    a=(a>=b)?a:b;
}
int main()
{
    int n, m; scanf("%d %d", &n, &m);
    for(int i=0; i<n; ++i) {
        scanf("%d", &c[i]);
        for(int j=0; j<c[i]; ++j) scanf("%d", &a[i][j]);
    }

    for(int i=0; i<n; ++i)
    for(int cnt=0; cnt<=c[i]; ++cnt) {
        int best=0;
        int size=c[i];
        for(int left=0; left<=cnt; ++left) {
            int right = cnt-left; assert(left <= size-right);
            int sum=0;
            for(int j=0; j<left; ++j) sum+=a[i][j];
            for(int j=size-1; j>=size-right; --j) sum+=a[i][j];
            best = max(best, sum);
        }
        dp[i][cnt]=best;
    }

    for(int row=0; row < n; ++row)
    for(int cnt=0; cnt <= m; ++cnt) {
        for(int curr=0; curr<=c[row] && curr+cnt <=m; ++curr) {
            chmax(total[row+1][cnt+curr], total[row][cnt] + dp[row][curr]);
        }
    }
    printf("%d\n", total[n][m]);
}
