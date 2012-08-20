// =========================================================
// 
//       Filename:  multiplyexceptself.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/11/2012 10:35:15 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/11/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

typedef long long int64;

int64 left[1005], right[1005];
int64 a[1005];

int main()
{
    int64 n; scanf("%lld", &n);
    for(int i=0; i<n; ++i)
        scanf("%lld", a+i);

    left[0] = 1;
    for(int i=1; i<n; ++i)
        left[i] = left[i-1] * a[i-1];
    right[n-1] = 1;
    for(int i=n-2; i>=0; --i)
        right[i] = right[i+1] * a[i+1];
        
    for(int i=0; i<n; ++i) {
        printf("%lld\n", left[i] * right[i]);
    }
}
