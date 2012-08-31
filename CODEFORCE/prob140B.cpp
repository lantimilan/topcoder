// =========================================================
// 
//       Filename:  prob140B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/04/2012 07:35:09 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/04/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int main()
{
    int a[305][305];
    int n; scanf("%d", &n);
    for(int i=1; i<=n+1; ++i)
        for(int j=1; j<=n; ++j)
            scanf("%d", &a[i][j]);

    int card[305];
    for(int i=1; i<=n; ++i)
    for(int k=1; k<=n; ++k)
    if (a[i][k]!=i)
    {
        bool good=true;
        int j;
        for(j=1; j<=n; ++j) 
        {
            if (a[n+1][j]==a[i][k]) break;
        }
        for(int jj=1; jj<j; ++jj) {
            if (a[n+1][jj]!=i && a[n+1][jj]<a[n+1][j]) {
                good=false; break;
            }
        }
        if (good) { card[i]=a[n+1][j]; break; }
    }
    for(int i=1; i<=n; ++i) {
        if (i>1) putchar(' ');
        printf("%d", card[i]);
    }
    puts("");
}
