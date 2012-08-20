// =========================================================
// 
//       Filename:  test.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/07/2012 08:37:48 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/07/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
using namespace std;

int main()
{
    double d1, d2;
    scanf("%lf", &d1);
    d2=1.999999999;

    d1*=1000000000;
    d2*=1000000000;
    printf("d1 %.10f\n", d1);
    printf("d2 %.10f\n", d2);
    assert(d1==d2);
}
