// =========================================================
// 
//       Filename:  prob3B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/11/2011 09:00:14 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/11/2011, LI YAN
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

template<class T>
void checkmax(T &a, T b)
{ a = (a>=b)?a:b; }

void solve()
{
    int n,v; cin >> n >> v;
    vector<PII> one, two;
    for(int i=0; i<n; ++i) {
        int t, p; cin >> t >> p;
        if (t==1) one.PB(PII(p,i+1));
        else two.PB(PII(p,i+1));
    }
    sort(one.begin(), one.end()); reverse(one.begin(), one.end());
    sort(two.begin(), two.end()); reverse(two.begin(), two.end());
    

    VI pre1(sz(one)+1), pre2(sz(two)+1);
    for(int i=1; i<sz(pre1); ++i) pre1[i] += pre1[i-1]+one[i-1].first;
    for(int i=1; i<sz(pre2); ++i) pre2[i] += pre2[i-1]+two[i-1].first;

    int ans=0; int x[2]={0};
    for(int k=0; k<sz(pre1) && k<=v; ++k)
    {
        int s2 = min(sz(pre2)-1,(v-k)/2);
        int curr = pre1[k]+pre2[s2];
        if (curr > ans) { ans=curr; 
            x[0]=k; x[1] = s2;
        }
    }
    cout << ans << endl;
    VI boats;
    for(int i=0; i<x[0]; ++i) boats.PB(one[i].second);
    for(int i=0; i<x[1]; ++i) boats.PB(two[i].second);
    for(int i=0; i<sz(boats); ++i)
    { if (i) cout << ' '; cout << boats[i]; }
    cout << endl;
}

int main()
{
    solve();
}
