// =========================================================
// 
//       Filename:  prob108C.cpp
// 
//    Description:  http://codeforces.com/contest/108/problem/C
// 
//        Version:  1.0
//        Created:  09/16/2011 10:42:32 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/16/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

int main()
{
    int n, p; cin >> n >> p;
    vector<pii> in(n,pii(-1,-1)); // id,cap
    vector<pii> out(n,pii(-1,-1)); // id,cap
    for(int i=0; i<p; ++i)
    {
        int a,b,d; cin >> a >> b >> d; --a,--b;
        out[a]=pii(b,d);
        in[b]=pii(a,d);
    }

    int ans=0;
    vector<int> begin, end, vol;
    for(int i=0; i<n; ++i) if (in[i].first<0 && out[i].first>=0)
    {
        int node=i;
        int cap=1<<30;
        while(out[node].first>=0) {
            int next=out[node].first, diam=out[node].second;
            cap=min(cap,diam); node=next;
        }
        ++ans; begin.push_back(i); end.push_back(node); vol.push_back(cap);
    }
    cout << ans << endl;
    for(int i=0; i<ans; ++i)
        cout << (begin[i]+1) << ' ' << (end[i]+1) << ' ' << vol[i] << endl;
}
