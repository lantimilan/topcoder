// =========================================================
// 
//       Filename:  prob140C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/04/2012 07:48:49 AM
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
#include <map>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

map<int,int> mpcnt;
typedef pair<int,int> pii;

int main()
{
    int n; scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        int d; scanf("%d", &d);
        mpcnt[d]++;
    }
    priority_queue<pii> pq;
    for(map<int,int>::iterator it=mpcnt.begin(); it!=mpcnt.end(); ++it)
    {
        pq.push(pii(it->second, it->first));
    }

    int ball[100000+5][3];
    int ans=0;
    while(!pq.empty()) {
        pii p[3];
        for(int i=0; i<3; ++i) {
            if (pq.empty()) break;
            p[i]=pq.top(); pq.pop();
        }
        if (p[2].first==0) break;
        for(int i=0; i<3; ++i) {
            ball[ans][i]=p[i].second;
            p[i].first--;
            if (p[i].first>0) pq.push(p[i]);
        }
        ++ans;
    }

    printf("%d\n", ans);
    for(int i=0; i<ans; ++i) {
        vector<int> v(3);
        for(int y=0; y<3; ++y) v[y]=ball[i][y];
        sort(v.begin(), v.end());
        printf("%d %d %d\n", v[2], v[1], v[0]);
    }
}
