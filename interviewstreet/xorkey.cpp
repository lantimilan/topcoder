// =========================================================
// 
//       Filename:  xorkey.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/06/2012 04:42:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/06/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;

typedef unsigned short ushort;

struct node_t {
    int begin, end;
    int x0, x1; // index into sorted[]
};

ushort unsorted[100005];
ushort sorted[2*1000005];
int N, NN, Q; 
int SN;

node_t vec[2*100005];

void construct()
{
    SN=0;
    NN=2*N-1;
    int n=N; while(n&(n-1)) n&=n-1; n=2*n-1;
    for(int i=n, j=0; i<2*n; ) {
        if (i<NN) { 
            vec[i].begin=vec[i].end=j;
            vec[i].x0=SN; vec[i].x1=SN+1;
            sorted[SN++]=unsorted[j];
            i++, j++;
        }
        else {
            int p=(i-1)/2;
            vec[p].begin=vec[p].end=j;
            vec[p].x0=SN; vec[p].x1=SN+1;
            sorted[SN++]=unsorted[j];
            i+=2, j++;
        }
    }
    for(int p=n-1; p>=0; --p) {
        int ll=2*p+1, rr=2*p+2; if (rr >= NN) continue;
        vec[p].begin = vec[ll].begin;
        vec[p].end   = vec[rr].end;
        vec[p].x0=SN;
        int xll=vec[ll].x0, xrr=vec[rr].x0;
        for(; xll<vec[ll].x1 && xrr<vec[rr].x1; ) {
            if (sorted[xll] < sorted[xrr]) {
                sorted[SN++]=sorted[xll]; ++xll;
            }
            else {
                sorted[SN++]=sorted[xrr]; ++xrr;
            }
        }
        for(; xll<vec[ll].x1; ++xll) sorted[SN++]=sorted[xll];
        for(; xrr<vec[rr].x1; ++xrr) sorted[SN++]=sorted[xrr];
        vec[p].x1=SN;
    }
}

ushort binsearch(int i, int j, ushort val)
{
    int ll=i, rr=j;
    while(ll<rr) {
        int m=(ll+rr+1)/2;
        if (sorted[m]<= val) ll=m;
        else rr=m-1;
    }
    return sorted[ll];
}

ushort search(ushort v, int p, int i, int j, int id)
{
    if (vec[id].begin > j || vec[id].end < i) return (ushort)-1;

    if (i<=vec[id].begin && vec[id].end<=j) {
        ushort mask = ~((1<<p)-1);
        ushort c = binsearch(vec[id].x0, vec[id].x1-1, v|((1<<p)-1));

        if (((c^v)&mask) == 0) return v & mask;
        else return (ushort)-1;
    }
    // recurse into children
    int ll=id*2+1, rr=id*2+2;
    ushort curr=-1;
    if (ll<NN) curr=search(v, p, i, j, ll);
    if (curr!=(ushort)-1) return curr;
    if (rr<NN) curr=search(v, p, i, j, rr);
    if (curr!=(ushort)-1) return curr;
    return (ushort)-1;
}

ushort query(ushort v, int i, int j)
{
    ushort target = ~v & ((1<<15)-1); // flip bit 0-14 and clear bit >=15
    //printf("query %hu target %hu\n", v, target);
    ushort ans=0U;
    for(int p=14; p>=0; --p) {
        ushort curr = ans | (1<<p & target);
        curr = search(curr, p, i, j, 0);
        if (curr != ushort(-1)) ans=curr;
        else ans |= 1<<p & v;
    }
    return ans^v;
}

void solve()
{
    scanf("%d%d", &N, &Q);
    for(int i=0; i<N; ++i) { 
        scanf("%hu", &unsorted[i]);
    }
    construct(); // very slow
    //puts("construct done");
    for(int q=0; q<Q; ++q) {
        ushort v;
        int i, j; 
        scanf("%hu%d%d", &v, &i, &j); --i, --j;
        ushort ans = query(v, i, j);
        printf("%hu\n", ans);
    }
    //puts("query done");
}


int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}

// after maintain a sorted[] array, got through 10 cases, still miss one
// my interval tree is not efficient
//
// XOR key  C++     
// Time Limit Exceeded
// 10/11 testcases passed
// 40 Point(s)  View Submission     Processed   2012-01-15 21:21 UTC
//
// XOR key  C++     
// Time Limit Exceeded
// 1/11 testcases passed
// 2 Point(s)   View Submission     Processed   2012-01-15 19:31 UTC
//
// XOR key  C++     
// Time Limit Exceeded
// 1/11 testcases passed
// 2 Point(s)   View Submission     Processed   2012-01-14 20:56 UTC
