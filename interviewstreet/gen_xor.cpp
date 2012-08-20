// =========================================================
// 
//       Filename:  gen_xor.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/14/2012 12:48:24 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/14/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand((unsigned)time(0));
    int N=100000, Q=50000;
    printf("%d %d\n", N, Q);
    for(int i=0; i<N; ++i) {
        printf("%d ", rand()%(1<<15));
    }
    putchar('\n');
    for(int q=0; q<Q; ++q) {
        int a=rand()%(1<<15);
        int i=rand()%N; ++i;
        int j=rand()%N; ++j;
        if (i>j) swap(i,j);
        printf("%d %d %d\n", a, i, j);
    }
}
