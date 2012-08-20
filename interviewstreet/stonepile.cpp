// =========================================================
// 
//       Filename:  stonepile.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/14/2012 10:36:13 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/14/2012, LI YAN
// 
// =========================================================

// This is a hard problem
// if you do not know Sprague-Grundy theory
//
// basically consider 1 pile with n<=50 stones
// let g(n) be the SG number of n
// the theory says that with k piles, the resulting
// g(a1,...,ak) is xor of each g(ai)
// and it is loss if g()=0, win otherwise
// to compute g(n) you only need to generate all partitions and for each partition 
// take xor of them
// g(n) is then the first number in N0 that does not appear in any partition
//
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

int used[55];
int sg[55];
int target;
int val;

//
// set up used bit for next conf
//
void part(int rem, int next, int curr)
{
    if (rem==0) { used[curr]=1; return; }
    for(int i=next; i<=rem; ++i) {
        part(rem-i, i+1, curr^sg[i]);
    }
}

//
// compute sg[k]=mex(union of all next conf[]
//
int calc(int k)
{
    int ans;
    memset(used, 0, sizeof used);
    for(int i=1; i<=k/2; ++i) {
        part(k-i, i+1, sg[i]);
    }
    for(ans=0; used[ans]; ++ans) {
        assert(ans<=50);
    }

    return ans;
}

void init()
{
    sg[1]=sg[2]=0;
    for(int i=3; i<=50; ++i)
        sg[i]=calc(i);
//    for(int i=1; i<=50; ++i) printf("%d: %d\n", i, sg[i]);
}

void solve()
{
    int N; scanf("%d", &N);
    int a[55];
    for(int i=0; i<N; ++i) scanf("%d", &a[i]);

    int ans=0;
    for(int i=0; i<N; ++i) ans ^=sg[a[i]];
    if (ans==0) puts("BOB");
    else puts("ALICE");
}

int main()
{
    init();
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t) {
        solve();
    }
}
