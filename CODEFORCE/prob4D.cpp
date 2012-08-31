// =========================================================
// 
//       Filename:  prob4D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/12/2011 05:38:17 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/12/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair
#define sz(x) int(x.size())

void solve()
{
    int n, w, h; cin >> n >> w >> h;
    vector<pair<PII,int> > elems;
    for(int i=0; i<n; ++i) {
        int ww, hh; cin >> ww >> hh;
        if (ww>w && hh>h) elems.PB(make_pair(PII(ww,hh),i+1));
    }
    if (elems.empty()) { cout << "0" << endl; return; }
    n=sz(elems); elems.PB(make_pair(PII(0,0), 0));
    sort(elems.begin(), elems.end());


    int chain[5050]={0};
    int prev[5050]; memset(prev,-1,sizeof prev);
    for(int k=1; k<=n; ++k)
    {
        int wk = elems[k].first.first, hk = elems[k].first.second;
        for(int j=0; j<k; ++j)
        {
            int ww = elems[j].first.first, hh=elems[j].first.second;
            if (wk>ww && hk>hh) {
                if (chain[k] < chain[j]+1) { chain[k] = chain[j]+1; prev[k]=j; }
            }
        }
    }
    VI ans; int best=0;
    for(int i=1; i<=n; ++i) { if (chain[i]>chain[best]) best=i; }
    for(int k=best; k>0; k=prev[k]) { assert(k>0); ans.PB(elems[k].second); }
    reverse(ans.begin(), ans.end());
    cout << sz(ans) << endl;
    for(int i=0; i<sz(ans); ++i) { if (i) cout << ' ';
        cout << ans[i]; }
    cout << endl;
}

int main()
{
    solve();
}
