// =========================================================
// 
//       Filename:  LEBOMBS.cpp
// 
//    Description:  http://www.codechef.com/AUG12/problems/LEBOMBS
// 
//        Version:  1.0
//        Created:  08/01/2012 09:00:37 PM
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
    int T; scanf("%d", &T);
    while(T--) {
        int N; scanf("%d", &N);
        char s[1024]; scanf("%s", s);
        int a[1024]={0};
        for(int i=0; i<N; ++i) if (s[i]=='1') {
            a[i]=1;
            if (i-1>=0) a[i-1]=1;
            if (i+1<N) a[i+1]=1;
        }
        int ans=0;
        for(int i=0; i<N; ++i) ans += (a[i]==0);
        printf("%d\n", ans);
    }
}
