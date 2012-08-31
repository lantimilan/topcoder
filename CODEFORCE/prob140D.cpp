// =========================================================
// 
//       Filename:  prob140D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/04/2012 08:12:48 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/04/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
    int n; scanf("%d", &n);
    int a[105];
    for(int i=0; i<n; ++i) scanf("%d", &a[i]);
    sort(a, a+n);

    int total=10;
    int sum=720;
    int mark=360;
    int ans=0, penalty=0;
    for(int i=0; i<n; ++i) {
        total += a[i];
        if (total <= sum) { ans++; 
            if (total>=mark) penalty += total-mark;
        }
        else break;
    }
    printf("%d %d\n", ans, penalty);
}
