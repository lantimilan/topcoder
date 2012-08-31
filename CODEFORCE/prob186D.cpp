// =========================================================
// 
//       Filename:  prob186D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/04/2012 09:29:46 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/04/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int main()
{
    int S; scanf("%d", &S);
    int a, b, c; scanf("%d%d%d", &a, &b, &c);
    double x, y, z;

    if (a+b+c==0) x=y=z=S/3.0;
    else {
        x = 1.0*a/(a+b+c)*S;
        y = 1.0*b/(a+b+c)*S;
        z = 1.0*c/(a+b+c)*S;
    }
    printf("%.10lf %.10lf %.10lf\n", x, y, z);
}
