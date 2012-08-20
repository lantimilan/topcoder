// =========================================================
// 
//       Filename:  ant.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/29/2012 10:24:55 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/29/2012, LI YAN
// 
// =========================================================


#include <algorithm>
#include <cstdio>
using namespace std;

const int P = 1000000000+6;
int a[1005];
int main()
{
    int N; scanf("%d", &N);
    for(int i=0; i<N; ++i)
        scanf("%d", a+i);

    sort(a, a+N);
    long long ans=0;
    for(int s=0; s<N; ++s) {
    long long curr=0;
    for(int i=0; i<N/2; i++) {
        for(int j=N/2; j<N; j++) {
            int t1 = abs(a[i]-a[j])*10/2;
            int meet = 1 + (P-t1)/(1000*10/2);
            curr += meet;
        }
    }
    ans = max(ans, curr);
    int t=a[0];
    for(int i=0; i<N-1; ++i) a[i] = a[i+1];
    a[N-1]=t;
    }
    printf("%lld\n", ans*2);
}
