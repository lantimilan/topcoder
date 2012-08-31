// =========================================================
// 
//       Filename:  prob219C.cpp
// 
//    Description:  http://codeforces.com/contest/219/problem/C
// 
//        Version:  1.0
//        Created:  08/30/2012 08:13:50 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/30/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
using namespace std;

char line[500000+5];
char res[500000+5];
int dp[500000+5][30];
int pred[500000+5][30];
const int MAX = 500000+100;

int main()
{
    int n, k; scanf("%d%d ", &n, &k);   
    gets(line);
    // dp[0][k] = 0
    for(int i=1; i<=n; ++i)
    for(int j=0; j<k; ++j)
        dp[i][j] = MAX;

    for(int i=0; i<n; ++i)
        for(int p=0; p<k; ++p)
        for(int j=0; j<k; ++j) if (j!=p)
        {
            int cur = dp[i][p];
            if (line[i]-'A' != j)
                cur++;
            if (cur < dp[i+1][j]) {
                dp[i+1][j] = cur;
                pred[i+1][j] = p;
            }
        }
    int ans = MAX, last=-1;
    for(int j=0; j<k; ++j) { 
        if (dp[n][j] < ans) {
            ans = dp[n][j];
            last = j;
        }
    }
    printf("%d\n", ans);
    assert(last >= 0);
    for(int i=n; i>0; --i) {
        res[i-1] = char('A' + last);
        last = pred[i][last];
    }
    puts(res);
}
