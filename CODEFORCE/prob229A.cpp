// =========================================================
// 
//       Filename:  prob229A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/02/2012 04:31:02 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/02/2012, LI YAN
// 
// =========================================================

// left[i][j] is col of left 1 for table[i][j]
// right[i][j] is col of right 1 for table[i][j]
//
// for each (i,j), only immediate left 1 and right 1 is useful
// need to have copy, row, copy to allow cyclic shift

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

char table[105][10000+5];
int left[105][100005];
int right[105][100005];

int main()
{
    int n, m; scanf("%d %d ", &n, &m);
    for(int i=0; i<n; ++i) {
        gets(table[i]);
    }
    memset(left, -1, sizeof left);
    memset(right, -1, sizeof right);
    
    bool good = true;
    for(int i=0; i<n; ++i) {
        int last;
        for(last=m-1; last >= 0; --last)
            if (table[i][last] == '1') break;
        if (last < 0) good = false;
        last -= m;
        for(int j=0; j<m; ++j) {
            if (table[i][j] == '1') { last = j; }
            left[i][j] = last;
        }
    }
    for(int i=0; i<n; ++i) {
        int last;
        for(last=0; last<m; ++last)
            if (table[i][last] == '1') break;
        last += m;
        for(int j=m-1; j>=0; --j) {
            if (table[i][j] == '1') { last = j; }
            right[i][j] = last;
        }
    }

    if (!good) {
        puts("-1"); return 0;
    }
    int ans = -1;
    for(int col=0; col<m; ++col) {
        int sum = 0;
        for(int i=0; i<n; ++i) {
            int d1, d2;
            d1 = col - left[i][col];
            d2 = right[i][col] - col;
            sum += min(d1, d2);
        }
        if (ans < 0) ans = sum;
        else if (ans > sum) ans = sum;
    }
    printf("%d\n", ans);
}

// Accepted
