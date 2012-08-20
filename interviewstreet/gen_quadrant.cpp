// =========================================================
// 
//       Filename:  gendata.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/07/2012 07:11:29 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/07/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    int N=13;
    printf("%d\n", N);
    for(int i=0; i<N; ++i) {
        int x = rand()%1009;
        if (x==0) x=1;
        if (rand()%2) x=-x;
        int y = rand()%1009;
        if (y==0) y=1;
        if (rand()%2) y=-y;
        printf("%d %d\n", x, y);
    }
    int Q=10+2;
    printf("%d\n", Q);
    for(int i=0; i<Q; i++) {
        int c = rand()%3;
        int ll = rand()%N; if (ll==0) ++ll;
        int rr = rand()%N; if (rr==0) ++rr;
        if (ll>rr) swap(ll,rr);
        switch(c) {
        case 0: printf("C %d %d\n", ll, rr); break;
        case 1: printf("X %d %d\n", ll, rr); break;
        case 2: printf("Y %d %d\n", ll, rr); break;
        }
    }
}
