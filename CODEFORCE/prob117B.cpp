// =========================================================
// 
//       Filename:  prob117B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/23/2011 08:59:47 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/23/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int a,b,mod; cin >> a >> b >> mod;

    //if (b>=mod-1) { // b covered all possible rem
    //    printf("2\n");
    //    return 0;
    //}
    
    int ans=-1;
    int d = ((-1000000000)%mod+mod)%mod;
    for(int i=0; i<=min(a,mod); ++i)
    {
        if ((long long)i*d%mod >=b+1) { ans=i; break; }
    }
    if (ans<0) printf("2\n");
    else {
        printf("1 %09d\n", ans);
    }
}
