// =========================================================
// 
//       Filename:  prob92D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/26/2011 12:52:32 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/26/2011, LI YAN
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
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
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

int bsearch(const vector<PII> &vec, int val)
{
    int lo=0, hi=vec.size()-1, mid=0;
    while(lo<=hi) {
        mid = (lo+hi)/2;
        if (vec[mid].first == val) return mid;
        else if (vec[mid].first > val) lo=mid+1;
        else hi=mid-1;
    }
    return lo;
}

void solve()
{
    int N; cin >> N;
    VI age(N);
    for(int i=N-1; i>=0; --i) cin >> age[i];
    VI ans(N);
    vector<PII> prev;
    for(int i=0; i<N; ++i) 
    {
        int pos = bsearch(prev, age[i]-1);
        if (pos >= sz(prev)) { prev.PB(MP(age[i],i)); ans[i]=-1; }
        else { ans[i] = i-prev[pos].second-1; }
    }

    for(int i=N-1; i>0; --i) cout << ans[i] << " ";
    cout << ans[0] << endl;
}

int main()
{
    solve();
}
