// =========================================================
// 
//       Filename:  prob123B.cpp
// 
//    Description:  http://codeforces.com/contest/123/problem/B
// 
//        Version:  1.0
//        Created:  11/04/2011 08:32:44 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 11/04/2011, LI YAN
// 
// =========================================================

// count number of lines x+y=2a 
// and number of lines x-y=2b that separate (x1,y1) from (x2,y2)
// since one point can be used to cross two lines, one being x+y=c1
// and the other x-y=c2
// ans is the max of the two numbers
#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
    int a,b,x1,y1,x2,y2; 
    scanf("%d%d%d%d%d%d", &a,&b,&x1,&y1,&x2,&y2);

    // x+y=k*2a
    int z1=x1+y1, z2=x2+y2;
    // z1 is large and z2 is small
    // large round down and small round up
    if (z1<z2) { swap(z1,z2); }
    if (z1>=0) { z1=z1/(2*a); }
    else { z1=z1/(2*a)-1; }
    if (z2>=0) { z2=z2/(2*a)+1; }
    else { z2=z2/(2*a); }
    int n1=z1-z2+1;

    // x-y=k*2b
    z1=x1-y1, z2=x2-y2;
    if (z1<z2) { swap(z1,z2); }
    if (z1>=0) { z1=z1/(2*b); }
    else { z1=z1/(2*b)-1; }
    if (z2>=0) { z2=z2/(2*b)+1; }
    else { z2=z2/(2*b); }
    int n2=z1-z2+1;

    int ans=max(n1,n2);
    printf("%d\n",ans);
}
