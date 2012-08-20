// =========================================================
// 
//       Filename:  gendata.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/11/2012 05:52:13 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/11/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


int main()
{
    srand((unsigned)time(0));
    int T=10000; printf("%d\n", T);
    for(int t=0; t<T; ++t) {
        long long A=(long long)((double)rand()/RAND_MAX * 1.0e18);
        long long B=(long long)((double)rand()/RAND_MAX * 1.0e18);
        printf("%lld %lld\n", min(A,B), max(A,B));
    }
}
