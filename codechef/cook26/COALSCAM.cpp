// =========================================================
// 
//       Filename:  COALSCAM.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/23/2012 04:53:13 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/23/2012, LI YAN
// 
// =========================================================

// stupid bug:
// nodes are numbered from 0 to N-1
// while I thought it was 1 to N
// the code would have passed test if T=1
// but as T=5 then we need to reinitialize id[0] to 0
//
// two phase of Kruskals
// for Chef[][] keep the max among parallel edges
// for Other[][] keep the min among parallel edges
//
// id[vertex] = root

#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

struct edge {
    int u, v;
    int c;
};

int N, M1, M2;
int comp;
edge Chef[20000+5];
edge Other[20000+5];
int id[5000+5];
int size[5000+5];

class LessCmp {
public:
    bool operator()(const edge& e1, const edge& e2) {
        return e1.c < e2.c;
    }
};

class MoreCmp {
public:
    bool operator()(const edge& e1, const edge& e2) {
        return e1.c > e2.c;
    }
};

int myfind(int u) {
    while(id[u] != u)
        u = id[u];
    return u;
}

void myunion(int u, int v)
{
    assert(id[u] == u && id[v] == v);
    if (size[u] > size[v]) {
        id[v] = u; size[u] += size[v];
    } else {
        id[u] = v; size[v] += size[u];
    }
}

void solve()
{
    scanf("%d%d%d", &N, &M1, &M2);
    comp = N;
    for(int i=0; i<M1; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        Other[i].u = u;
        Other[i].v = v;
        Other[i].c = c;
    }
    for(int i=0; i<M2; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        Chef[i].u = u;
        Chef[i].v = v;
        Chef[i].c = c;
    }

    sort(Other, Other+M1, LessCmp());
    sort(Chef, Chef+M2, MoreCmp());

    for(int i=0; i<N; ++i) { 
        id[i] = i; size[i] = 1;
    }

    long long ans1, ans2;
    ans1 = 0;
    for(int x=0; x<M2; ++x) {
        edge e = Chef[x];
        int pa, pb;
        pa = myfind(e.u);
        pb = myfind(e.v);
        if (pa == pb) continue;
        comp--;
        ans1 += e.c;
        myunion(pa, pb);
    }
    ans2 = ans1;
    for(int x=0; x<M1; ++x) {
        edge e = Other[x];
        int pa, pb;
        pa = myfind(e.u);
        pb = myfind(e.v);
        if (pa == pb) continue;
        comp--;
        ans2 += e.c;
        myunion(pa, pb);
    }
    if (comp == 1) {
        printf("%lld %lld\n", ans1, ans2);
    } else {
        puts("Impossible");
    }
}

int main()
{
    int T; scanf("%d", &T);
    while(T--)
        solve();
}

// Correct Answer
// Execution Time: 1.29
