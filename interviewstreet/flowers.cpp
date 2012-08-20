// =========================================================
// 
//       Filename:  flowers.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/14/2012 09:24:21 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/14/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
using namespace std;

typedef long long int64;
int cost[200];
int N, K;

int main()
{
    scanf("%d%d", &N, &K);
    for(int i=0; i<N; ++i) {
        scanf("%d", cost+i);
    }
    sort(cost, cost+N, greater<int>());

    int64 ans=0;
    for(int i=0; i<K; i++) {
        for(int j=0; i+j*K<N; j++) {
            ans += int64(cost[i+j*K])*(j+1);
        }
    }
    printf("%lld\n", ans);
}

// #    Status  Signal  Time
// 1    Passed  Success     0.050862
// 2    Passed  Success     0.050731
// 3    Passed  Success     0.050825
// 4    Passed  Success     0.050795
// 5    Passed  Success     0.050822
// 6    Passed  Success     0.051045
// 7    Passed  Success     0.050811
// 8    Passed  Success     0.050889
// 9    Passed  Success     0.050707
// 10   Passed  Success     0.050696
//
