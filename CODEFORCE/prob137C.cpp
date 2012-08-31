// =========================================================
// 
//       Filename:  prob137C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/15/2011 10:23:02 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/15/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

typedef pair<int,int> pii;

pii range[100000+5];

int main()
{
    int n; scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%d%d", &range[i].first, &range[i].second);
    }
    sort(range, range+n);

    int ans=0;
    for(int i=0; i<n; ) {
        int a1=range[i].first, b1=range[i].second;
        int j;
        for(j=i+1; j<n; ++j) {
            int a2=range[j].first, b2=range[j].second;
            if (b1>b2) ans++;
            else break;
        }
        i=j;
    }
    printf("%d\n", ans);
}
