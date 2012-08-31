// =========================================================
// 
//       Filename:  prob136D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/21/2011 03:36:29 PM
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
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int,pii> key;

bool isrect(const vector<key> &pts, int s)
{
    for(int i=0; i<4; ++i) {
        pii p1,p2,p3;
        p1 = pts[s+i].second;
        p2 = pts[s+(i+1)%4].second;
        p3 = pts[s+(i+2)%4].second;
        pii d1, d2;
        d1.first = p2.first-p1.first;
        d1.second = p2.second-p1.second;
        d2.first = p3.first-p2.first;
        d2.second = p3.second-p2.second;

        pii ans;
        ans.first  = d2.first*d1.first + d2.second*d1.second;
        ans.second = d2.first*(-d1.second) + d2.second*d1.first;

        if (ans.first==0 && ans.second < 0) continue;
        else return false;
    }
    return true;
}

bool issquare(const vector<key> &pts, int s)
{
    if (!isrect(pts,s)) return false;
    int d[4];
    for(int i=0; i<4; ++i) {
        pii p1, p2;
        p1 = pts[s+i].second;
        p2 = pts[s+(i+1)%4].second;
        int d1=p1.first-p2.first, d2=p1.second-p2.second;
        d[i]=d1*d1+d2*d2;
    }
    for(int i=0; i+1<4; ++i) {
        if (d[i]!=d[i+1]) return false;
    }
    return true;
}

int main()
{
    vector<key> pts(8);
    for(int i=0; i<8; ++i) {
        pts[i].first=i+1;
        scanf("%d%d", &pts[i].second.first, 
            &pts[i].second.second);
    }
    bool found=false;
    do {
        //for(int i=0; i<8; ++i) cout << pts[i].second << ' '; cout << endl;
        if (issquare(pts,0) && isrect(pts,4)) {
            found=true; break;
        }
    } while(next_permutation(pts.begin(), pts.end()));
    if (found) {
        puts("YES");
        for(int i=0; i<8; ++i) {
            if (i%4 != 0) putchar(' ');
            if (i==4) puts("");
            printf("%d", pts[i].first);
        }
        puts("");
    }
    else {
        puts("NO");
    }
}
