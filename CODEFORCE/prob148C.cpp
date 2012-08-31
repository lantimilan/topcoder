// =========================================================
// 
//       Filename:  prob148C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/05/2012 09:16:06 PM
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

int main()
{
    int n, a, b; scanf("%d%d%d", &n, &a, &b);
    int ta=a, tb=b;
    int s[105]; 
    int x=0, sum;
    s[0]=1; sum=s[0];
    while(b--) {
        s[++x] = sum+1;
        sum+=s[x];
    }
    if (s[x]>50000) { printf("-1\n"); return 0; }
    int t=s[x];
    for(++x; x<n-a; ++x) s[x]=t;
    for(; x<n; ++x) s[x]=s[x-1]+1;
    if (s[n-1]>50000) { printf("-1\n"); return 0; }
    else {
        int ca, cb, sum;
        ca=cb=0; sum=s[0];
        for(int i=1; i<n; ++i) {
            if (s[i]>sum) cb++;
            else if (s[i]>s[i-1]) ca++;
            sum += s[i];
        }
        if (ca!=ta || cb!=tb) {
            printf("-1\n"); return 0;
        }
        for(int i=0; i<n; ++i) {
            if (i) putchar(' ');
            printf("%d", s[i]);
        }
        putchar('\n');
    }
}
