// =========================================================
// 
//       Filename:  prob109A.cpp
// 
//    Description:  http://codeforces.com/contest/109/problem/A
// 
//        Version:  1.0
//        Created:  09/09/2011 10:34:48 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/09/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int main()
{
    int n; scanf("%d",&n);

    pii best=pii(n,n);
    // 4*a + 7*b = n
    for(int a=0; a<=n/4; ++a)
    {
        if ((n-4*a)%7!=0) continue;
        int b = (n-4*a)/7;
        if (a+b<best.first+best.second) best=pii(a,b);
        else if (a+b==best.first+best.second && a>best.first) best=pii(a,b);
    }

    int a=best.first, b=best.second;
    if (a>=n) { printf("%d\n",-1); return 0; }
    for(int i=0; i<a; ++i) printf("%d",4);
    for(int i=0; i<b; ++i) printf("%d",7);
    printf("\n");
}
