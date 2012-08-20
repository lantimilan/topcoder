// =========================================================
// 
//       Filename:  BLOCK.cpp
// 
//    Description:  http://www.codechef.com/AUG12/problems/BLOCKING 
// 
//        Version:  1.0
//        Created:  08/09/2012 10:30:27 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/09/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int myindex[105];
int location[105]; // location[boy] = house
vector<pii> visit[105]; // boy, [(time, house)]

int main()
{
    int n; scanf("%d", &n);
    for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j) {
        int t; scanf("%d", &t);
        visit[i].push_back(pii(t,j));
    }
    for(int i=0; i<n; ++i) {
        myindex[i] = 0;
        sort(visit[i].begin(), visit[i].end());
    }

    bool ans = false;
    while(true) {
        for(int i=0; i<n; ++i) {
            location[i] = visit[i][myindex[i]].second;
        }
        // find min time of a conflict boy
        int cnt[105] = {0};
        for(int b=0; b<n; ++b) {
            int h = location[b];
            cnt[h]++;
        }
        int house=-1;
        for(int h=0; h<n; ++h) if (cnt[h] > 1) { house=h; break; } 
        if (house < 0) { ans=true; break; }
        int bmin=-1, tmin;
        for(int b=0; b<n; ++b) if (location[b] == house){
            int tnow = visit[b][myindex[b]].first;
            if (bmin < 0 || tnow < tmin) {
                bmin = b; tmin = tnow;
            }
        }
        assert(bmin>=0);
        myindex[bmin]++;
        if (myindex[bmin]>=n) break;
    }
    
    if (ans) {
        for(int i=0; i<n; ++i) {
            if (i) putchar(' ');
            printf("%d", visit[i][myindex[i]].second+1);
        }
        putchar('\n');
    }
    else printf("%d\n", -1);
}
