// =========================================================
// 
//       Filename:  SAD.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/01/2012 08:44:33 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int R, C;
int a[105][105];

int main()
{
    scanf("%d%d", &R, &C);
    for(int i=0; i<R; ++i)
    for(int j=0; j<C; ++j)
        scanf("%d", &a[i][j]);

    int ans=-1;
    for(int i=0; i<R; ++i)
    for(int j=0; j<C; ++j)
    {
        bool good=true;
        int val = a[i][j];
        for(int i2=0; i2<R; ++i2)
            if (a[i2][j] > val) good=false;
        for(int j2=0; j2<C; ++j2)
            if (a[i][j2] < val) good=false;
        if (good) ans=val;
    }
    if (ans>0) printf("%d\n", ans);
    else puts("GUESS");
}
