// =========================================================
// 
//       Filename:  prob6E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/18/2011 08:33:08 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/18/2011, LI YAN
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
void chmax(T &a, T b) { a = a>=b ? a:b; }

template<class T>
void chmin(T &a, T b) { a = a<=b ? a:b; }

void solve()
{
    int n, k; cin >> n >> k;
    VI h(n); for(int i=0; i<n; ++i) cin >> h[i];
    int cnt[1000000+5] = {0};

    set<int> seen;
    int maxrun=0, prev=0;
    vector<PII> subs;
    for(int i=0; i<n; ++i)
    {
        cnt[h[i]]++; seen.insert(h[i]);

        int vmin, vmax;
        vmin = *seen.begin();
        vmax = *(--seen.end()); //cout << vmin << ' ' << vmax << endl;
        assert(vmax>=vmin);
        if (vmax-vmin <= k) {
            int curr = i-prev+1;
            if (curr > maxrun) {
                maxrun = curr; subs.clear(); subs.PB(PII(prev,i));
            }
            else if (curr==maxrun) { subs.PB(PII(prev,i)); }
        }
        else {
            for(int p=prev; p<=i; ++p) {
                assert(cnt[h[p]]>0);
                if (--cnt[h[p]] == 0) seen.erase(h[p]);
                vmin = *seen.begin();
                vmax = *(--seen.end());
                if (vmax-vmin <= k) { prev=p+1; break; }
            }
            assert(prev<=i);
            int curr = i-prev+1;
            if (curr > maxrun) {
                maxrun = curr; subs.clear(); subs.PB(PII(prev,i));
            }
            else if (curr==maxrun) { subs.PB(PII(prev,i)); }
        }
    }
    cout << maxrun << ' ' << sz(subs) << endl;
    for(int i=0; i < sz(subs); ++i)
        cout << subs[i].first+1 << ' ' << subs[i].second+1 << endl;
}

int main()
{
    solve();
}
