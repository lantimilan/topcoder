// =========================================================
// 
//       Filename:  DREAM.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/01/2012 10:44:04 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/01/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int N, K;
pii a[100005];

int main()
{
    scanf("%d%d", &N, &K);
    for(int i=0; i<N; ++i)
    {
        int x; scanf("%d", &x);
        a[i]=pii(x,i);
    }
    sort(a, a+N);
    int ans=0;
    for(int i=0; i<N; ) {
        int v=a[i].first; 
        int pos=a[i].second;
        ans++; i++;
        while(i<N && a[i].first==v && a[i].second < pos+K)
            i++;
    }
    printf("%d\n", ans);
}
