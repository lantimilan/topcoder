// =========================================================
// 
//       Filename:  gen_meetpoint.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/16/2012 09:36:33 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/16/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand((unsigned)time(0));
    int n=100; printf("%d\n", n);
    for(int i=0; i<n; ++i) {
        int x=rand()%1000000007; if (rand()%2) x=-x;
        int y=rand()%1000000007; if (rand()%2) y=-y;
        printf("%d %d\n", x, y);
    }
}
