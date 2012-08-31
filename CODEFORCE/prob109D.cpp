// =========================================================
// 
//       Filename:  prob109D.cpp
// 
//    Description:  http://codeforces.com/contest/109/problem/D
// 
//        Version:  1.0
//        Created:  09/12/2011 02:10:02 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/12/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <set>
#include <utility>
#include <vector>
using namespace std;

#define sz(a) int(a.size())

typedef pair<int,int> pii;

set<pii> elems;

int main()
{
    int n; scanf("%d",&n);
    int lucky=-1,luckypos=-1;
    vector<int> vec(n);
    for(int i=0; i<n; ++i)
    {
        int k; scanf("%d",&k);
        vec[i]=k;
        elems.insert(pii(k,i));
        bool islucky=true;
        int tmp=k;
        while(tmp) { 
            if (tmp%10!=4 && tmp%10!=7) { islucky=false; break; } 
            tmp/=10; 
        }
        if (islucky) { lucky=k; luckypos=i; }
    }
    bool issort=true;
    for(int i=0; i<n-1; ++i)
    { if (vec[i]>vec[i+1]) issort=false; }
    if (issort) { printf("0\n");; return 0; }
    if (lucky<0) { printf("-1\n");; return 0; }

    vector<pii> ans;
    for(int i=n-1; i>=0; --i)
    {
        // find max, swap last with lucky, then swap lucky with max
        set<pii>::iterator maxit = --elems.end();
        if (maxit->second==i) { // max elem at last pos
            elems.erase(maxit); continue; 
        }
        int val=vec[i]; 
        int p1,p2,p3; // luckypos, maxpos and lastpos
        p1=luckypos; p2=maxit->second; p3=i;
        ans.push_back(pii(p1,i)); // swap lucky and last
        ans.push_back(pii(p2,i)); // swap lucky and max
        vec[i]=maxit->first; vec[p2]=lucky; vec[p1]=val;
        elems.erase(maxit);
        elems.erase(pii(lucky,luckypos)); 
        elems.erase(pii(val,p3));
        luckypos=p2;
        pii e1,e2; e1=pii(val,p1); e2=pii(lucky,luckypos);
        elems.insert(e1); elems.insert(e2);
    }
    assert(elems.empty());
    printf("%u\n", ans.size());
    for(int i=0; i<sz(ans); ++i)
    {
        printf("%d %d\n", ans[i].first+1, ans[i].second+1);
    }
}
