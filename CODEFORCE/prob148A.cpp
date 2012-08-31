// =========================================================
// 
//       Filename:  prob148A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/05/2012 08:39:30 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 02/05/2012, LI YAN
// 
// =========================================================


#include <cstdio>
using namespace std;

int gcd(int a, int b)
{
    while(b) {
        int t=a;
        a=b; b=t%b;
    }
    return a;
}

int lcm(int a, int b)
{
    return (long long)a*b/gcd(a,b);
}

int main()
{
    int a[5]; 
    int d;
    int ans=0;
    for(int i=0; i<4; ++i) scanf("%d", &a[i]);
    scanf("%d", &d);

    for(int b=1; b<(1<<4); ++b) {
        int l=1;
        int cnt=0;
        for(int i=0; i<4; ++i) if (b & 1<<i) {
            l = lcm(l, a[i]); cnt++;
        }
        if (cnt&1) {
            ans += d/l;
        }
        else {
            ans -= d/l;
        }
        //printf("l %d, ans %d\n", l, ans);
    }
    printf("%d\n", ans);
}
