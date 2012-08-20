// =========================================================
// 
//       Filename:  INTTEST.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/01/2012 10:54:42 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int main()
{
    int n, k; scanf("%d%d", &n, &k);
    int ans=0;
    for(int i=0; i<n; ++i) {
        int a;
        scanf("%d", &a);
        if (a%k==0) ans++;
    }
    printf("%d\n", ans);
}
