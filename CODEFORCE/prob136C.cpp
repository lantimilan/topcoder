// =========================================================
// 
//       Filename:  prob136C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/21/2011 03:29:07 PM
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
using namespace std;

int main()
{
    int n; scanf("%d", &n);
    int a[100000+5];
    int maxval=0, maxid;
    for(int i=0; i<n; ++i) {
        scanf("%d", &a[i]);
        if (a[i]>maxval) { maxval=a[i]; maxid=i; }
    }
    if (maxval==1) { a[0]=2; }
    else { a[maxid]=1; }
    sort(a, a+n);
    for(int i=0; i<n; ++i) {
        if (i) putchar(' ');
        printf("%d", a[i]);
    }
    puts("");
}

