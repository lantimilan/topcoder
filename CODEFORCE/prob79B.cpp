// =========================================================
// 
//       Filename:  prob79B.cpp
// 
//    Description:  B. Colorful Field
// 
//        Version:  1.0
//        Created:  04/30/2011 08:15:45 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/30/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PI;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

void solve()
{
    int n,m,k,t; cin >> n >> m >> k >> t;
    set<PI> waste;
    set<PI> query;
    vector<PI> old(t);
    for(int i=0; i<k; ++i) { PI p; cin >> p.first >> p.second; waste.insert(p); }
    for(int i=0; i<t; ++i) { cin >> old[i].first >> old[i].second; }
    for(int i=0; i<t; ++i) query.insert(old[i]);

    //cout << n << " " << m << " " << k << " " << t << endl;

    map<PI,int> res;
    /*
    int cnt=0;
    for(int r=1; r<=n; ++r) for(int c=1; c<=m; ++c)
    {
        PI p = PI(r,c); int curr = cnt;
        if (waste.find(p) != waste.end()) { curr=3; }
        else { cnt=(cnt+1)%3; }
        if (query.find(p) != query.end())  res[p] = curr; //cout << "query " << res[p] << endl; }
        //cout << r << " " << c << " " << curr << endl;
    }
    */

    set<PI>::const_iterator itw=waste.begin(), itq=query.begin();

    int cnt=0;
    for(; itq!=query.end(); ++itq)
    {
        int r=itq->first, c=itq->second;
        while(itw!=waste.end() && *itw < *itq) { ++itw; ++cnt; }
        if (*itw == *itq) res[*itq] = 3;
        else res[*itq] = ((r-1)*m+c-cnt-1)%3;
    }

    for(int i=0; i<(int)old.size(); ++i)
    {
        int crop = res[old[i]];
        string ss;
        switch(crop) {
        case 0: ss="Carrots"; break;
        case 1: ss="Kiwis"; break;
        case 2: ss="Grapes"; break;
        case 3: ss="Waste"; break;
        }
        cout << ss << '\n';
    }
}

int main()
{
    solve();
}

/* ***********
 *  #   When    Who     Problem     Lang    Verdict     Time    Memory
 *  420794  May 1, 2011 9:56:56 AM  lantimilan  B - Colorful Field  GNU C++
 *  Accepted    50 ms   1500 KB 
 * */
