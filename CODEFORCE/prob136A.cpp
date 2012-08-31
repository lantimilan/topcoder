// =========================================================
// 
//       Filename:  prob136A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/21/2011 02:32:42 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/21/2011, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int main()
{
    int n; scanf("%d", &n);
    int a[105];
    for(int i=1; i<=n; ++i) {
        scanf("%d", &a[i]);
    }
    int b[105];
    for(int i=1; i<=n; ++i) {
        b[a[i]]=i;
    }
    for(int i=1; i<=n; ++i) {
        if (i>1) putchar(' ');
        printf("%d", b[i]);
    }
    puts("");
}
