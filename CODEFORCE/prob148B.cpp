// =========================================================
// 
//       Filename:  prob148B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/05/2012 08:59:39 PM
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

const double EPS=1.0e-8;

int main()
{
    int vp, vd, t, f, c; 
    scanf("%d%d%d%d%d", &vp, &vd, &t, &f, &c);

    double princess, dragon; 
    int bijou;
    princess=dragon=0.0;
    bijou=0;

    if (vd<vp) {
        printf("0\n"); return 0;
    }

    princess += vp*t;
    while(princess < c-EPS) {
        double gap=(princess-dragon)/(vd-vp);
        princess+=vp*gap; dragon=princess;
        if (princess >= c-EPS) break;
        bijou++;
        gap=dragon/vd; gap+=f; dragon=0;
        princess += vp*gap;
    }
    printf("%d\n", bijou);
}
