// =========================================================
// 
//       Filename:  prob186B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/04/2012 08:38:45 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/04/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;

int height[1005];
typedef pair<int, int> pii;
pii hid[1005];

int main()
{
    int n, t1, t2, k; scanf("%d%d%d%d", &n, &t1, &t2, &k);
    for(int i=0; i<n; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        int h1, h2;
        h1 = a*t1*(100-k)+100*b*t2;
        h2 = b*t1*(100-k)+100*a*t2;
        height[i]=max(h1,h2);
        hid[i]=pii(-height[i], i+1);
    }
    sort(hid, hid+n);
    for(int i=0; i<n; i++) {
        printf("%d %.2f\n", hid[i].second, -hid[i].first/100.0);
    }
}
