// =========================================================
// 
//       Filename:  billboard.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/08/2012 03:53:03 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 02/08/2012, LI YAN
// 
// =========================================================

// algorithm: deque loss<val,pos> keeps the minimum loss if skip pos
// use O(1) time fixed window minimum query
//
// ternary search is wrong, two monotone sequence do not end up a unimodal seq
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <vector>
#include <utility>
using namespace std;

typedef long long int64;
typedef pair<int64, int> pii;

deque<pii> loss;

int a[100000+5];

void solve()
{
    int n, k; scanf("%d%d", &n, &k);
    for(int i=0; i<n; ++i) {
        scanf("%d", &a[i]);
    }
	loss.push_back(pii(0,0));
	for(int i=0; i<n; ++i) {
		int64 t=0;
		assert(!loss.empty());
		t+=loss.front().first;
		t+=a[i];
		while(loss.front().second <= i-k) loss.pop_front();
		while(!loss.empty() && loss.back().first >= t) loss.pop_back();
		loss.push_back(pii(t,i+1));
	}
	int64 ans=0;
	for(int i=0; i<n; ++i) ans+=a[i];
	ans-=loss.front().first;
    printf("%lld\n", ans);
}

int main()
{
    solve();
}

