// =========================================================
// 
//       Filename:  topfour.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/11/2012 10:09:17 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/11/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
using namespace std;

int a[1000000+5];

void chmin(int &a, int b)
{
    a = a<b?a:b;
}

void chmax(int &a, int b)
{
    a = a>b?a:b;
}

int main()
{
    int n; scanf("%d", &n); assert(n>=4);
    int top[5];
    int bottom;

    for(int i=0; i<n; ++i) scanf("%d", a+i);
    bottom = a[0];
    for(int i=0; i<n; ++i) chmin(bottom, a[i]);

    for(int k=0; k<4; ++k) {
        int tmp = a[0], idx = 0;
        for(int i=0; i<n; ++i) {
            if (a[i] > tmp) {
                tmp = a[i]; idx = i;
            }
        }
        top[k] = tmp; a[idx] = bottom;
    }
    for(int k=0; k<4; ++k)
        printf("%d\n", top[k]);
}
