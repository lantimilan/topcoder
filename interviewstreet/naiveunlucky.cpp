// =========================================================
// 
//       Filename:  naiveunlucky.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/16/2012 05:58:30 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/16/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

typedef long long int64;

int64 a[1000000+5];

int main()
{
    int N;
    int64 K;
    scanf("%d%lld", &N, &K);
    for(int i=0; i<N; ++i) scanf("%lld", a+i);

    int ans=0;
    for(int64 i=1; i*i<=K; ++i) if (K%i ==0) {
        int64 x[2]; x[0]=i; x[1]=K/i;
        if (x[0]==x[1]) x[1]=0;
        for(int z=0; z<2 && x[z]; ++z) {
            bool good=true;
            for(int t=0; t<N; ++t) if (a[t]%x[z]==0)
                good=false;
            if (good) ans++;
        }
    }
    printf("%d\n", ans);
}
