// =========================================================
// 
//       Filename:  C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/13/2011 09:09:55 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/13/2011, LI YAN
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

map<int,int> cirmap; // xi id
map<PII,int> shotmap; // (xj,yj) id
map<int,int> hitmap; // xi -> id(xj,yj)

LL sqr(LL k) { return k*k; }

void solve()
{
    cirmap.clear(); shotmap.clear(); hitmap.clear();
    int n; cin >> n;
    vector<PII> circles(n);
    for(int i=0; i<n; ++i)
    { 
        int xi, ri;
        cin >> xi >> ri;
        circles[i] = PII(xi,ri);
        cirmap[xi] = i;
    }
    sort(circles.begin(), circles.end());

    VI right(n); for(int i=0; i<n; ++i) right[i]=circles[i].first+circles[i].second;
    int m; cin >> m;
    vector<PII> shots(m);
    for(int j=0; j<m; ++j)
    {
        int xj, yj; cin >> xj >> yj;
        shots[j] = PII(xj,yj);
        if (!shotmap.count(shots[j])) shotmap[shots[j]]=j; // shots can have duplicates
    }
    sort(shots.begin(), shots.end());

    for(int j=0; j<m; j++)
    {
        LL xj=shots[j].first, yj=shots[j].second;
        VI::iterator cit;
        cit = lower_bound(right.begin(), right.end(), xj);

        for(; cit!=right.end(); ++cit) // loop all circles
        {
            int i = cit-right.begin();
            assert(0<=i && i<n);
            //cout << "(" << shots[j].first << "," << shots[j].second << ") "
            //     << "(" << circles[i].first  << "," << circles[i].second << ")\n";
            if (xj < circles[i].first-circles[i].second ) break;

            LL xi=circles[i].first, yi=0, ri=circles[i].second;
            LL d2 = sqr(xi-xj) + sqr(yi-yj);
            if (d2 <= ri*ri)
            { 
                int newid = shotmap[PII(xj,yj)];
                if (!hitmap.count(xi) || hitmap[xi]>newid) hitmap[xi] = newid; 
            }
        }
    }
    VI ans(n,-1);
    fort(it,hitmap)
    {
        ans[cirmap[it->first]]=it->second+1;
    }
    cout << hitmap.size() << endl;
    for(int i=0; i<n; ++i)
    { if (i) cout << " "; cout << ans[i]; }
    cout << endl;
}

int main()
{
    solve();
}

/* ***********************
 * binary search
 *
 * 453912        May 14, 2011 2:11:43 AM    lantimilan        C - Biathlon
 * GNU C++       Accepted        780 ms      11200 KB
 * 453908   May 14, 2011 2:08:01 AM     lantimilan  C - Biathlon    GNU C++
 * Wrong answer on test 8   10 ms   1400 KB 
 * */
