// =========================================================
// 
//       Filename:  prob111B.cpp
// 
//    Description:  http://codeforces.ru/contest/111/problem/B
// 
//        Version:  1.0
//        Created:  09/07/2011 09:07:20 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/07/2011, LI YAN
// 
// =========================================================

// Algorithm:
// since x<=10^5, can enumerate sqrt(x)=10^2.5
// For all n<=10^5 numbers, it is 10^7.5
// Now need to check whether a divisor divides prev x[i-y_i] to x[i-1]
// cannot divide each x[i-y_i] to x[i-1] since this could cost another 10^5
// using the idea of prime factors also won't work 
//
// Now what to do?
//
// watashi's solution is to keep track of the last appearance of each divisor
// t[k]=i if integer k is a divisor of x[i] and no x[j] with j>i has divisor k
// Now for each divisor d of x[i], you can simply check whether t[d] is within
// y_i away from x[i]
//
#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
    int n; scanf("%d",&n);
    int t[100000+5]; fill(t,t+sizeof(t)/sizeof(int),-1);
    for(int i=0; i<n; ++i)
    {
        int x,y; scanf("%d%d",&x,&y); //fprintf(stderr,"%d %d\n",x,y);
        int ans=0;
        for(int d=1; d*d<=x; ++d) if (x%d==0)
        {
            if (y==0 || t[d]<i-y) { ans++; }
            t[d]=i;
            int d2=x/d;
            if (d2!=d) {
                if (y==0 || t[d2]<i-y) { ans++; }
                t[d2]=i;
            }
        }
        printf("%d\n",ans);
    }
}
