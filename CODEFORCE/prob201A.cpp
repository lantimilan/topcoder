// =========================================================
// 
//       Filename:  prob201A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/29/2012 08:59:35 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/29/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
using namespace std;

int main()
{
    int n; scanf("%d", &n);
    int size=-1;
    for(int k=0; ; k++) { // size = 2*k+1
        int total=(k+1)*(k+1) + k*k;
        if (total >= n) { size=2*k+1; break; }
    }
    assert(size>0);
    printf("%d\n", size);
}
