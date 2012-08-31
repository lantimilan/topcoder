// =========================================================
// 
//       Filename:  prob79C.cpp
// 
//    Description:  C. Beaver
// 
//        Version:  1.0
//        Created:  04/30/2011 09:18:24 AM
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
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PI;
typedef vector<PI> VII;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

void solve()
{
    string s; cin >> s;
    int n; cin >> n;
    vector<string> b(n);
    for(int i=0; i<n; ++i) cin >> b[i];

    VII vpos;
    int len=s.length();
    for(int p=0; p<len; ++p)
    for(int sub=1; sub<=10; ++sub)
    {
        string part=s.substr(p,sub);
        for(int i=0; i<n; ++i) if (b[i]==part) vpos.PB(PI(p,p+sub));
    }
    //sort(vpos.begin(), vpos.end());
    //VII:iterator it=unique(vpos.begin(), vpos.end());
    //vpos.resize(it-vpos.begin());

    /* 
    for(int i=0; i<int(vpos.size()); ++i)
        cout << "(" << vpos[i].first << "," << vpos[i].second << ") ";
    cout << endl;
    */

    PI best=PI(0,0);
    int begin=0, end, index=0;
    while(begin < len)
    {
        while(index<int(vpos.size()) && vpos[index].first < begin) ++index;
        if (index >= int(vpos.size())) { 
            end = len; 
            if (end-begin > best.second-best.first) { best = PI(begin,end); }
            begin=end;
        }
        else
        {
            end = vpos[index].second; int lim = end; // need lim to avoid TLE
            for(int k=index; k<int(vpos.size())&&vpos[k].first<lim; ++k)
            { if (end > vpos[k].second) { end = vpos[k].second; index=k;} }
            end--;
            if (end-begin > best.second-best.first) { best = PI(begin,end); }
            begin = vpos[index].first+1;
        }
        //cout << begin << " " << end << endl;
    }
    int bestn = best.second-best.first;
    cout << bestn << " " << best.first << endl;
}

int main()
{
    solve();
}
/***********
 * 420825        May 1, 2011 10:19:05 AM    lantimilan        C - Beaver     GNU
 * C++       Accepted        330 ms      13800 KB 
 *
 * 420810        May 1, 2011 10:08:19 AM    lantimilan        C - Beaver     GNU
 * C++       Time limit exceeded on test 38      2000 ms     3100 KB 
 *
 * 419543        Apr 30, 2011 8:58:42 PM    lantimilan        C - Beaver     GNU
 * C++       Wrong answer on pretest 4       30 ms       1364 KB 
 */
