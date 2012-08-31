// =========================================================
// 
//       Filename:  prob136B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/21/2011 02:39:31 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/21/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
    int a, c; scanf("%d%d", &a, &c);
    int b=0;
    int f=1;
    while(c || a) {
        int d = c%3 - a%3;
        if (d<0) d+=3;
        b += f*d;
        f*=3;
        c/=3; a/=3;
    }
    printf("%d\n", b);
}
