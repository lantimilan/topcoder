// =========================================================
// 
//       Filename:  prob6D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/18/2011 09:15:04 AM
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


int n,a,b;
int memo[20][20][20]; // h[p-1], h[p], p
int best[20][20][20]; // at h[p-1],h[p],p, how many fireballs to attack pos p

int calc(VI conf, int p)
{
//cout << p << ' ' << conf[p] << ' ' << conf[p-1] << endl;

    if (p>=sz(conf)-1) {
        if (conf[sz(conf)-2]<=0 && conf[sz(conf)-1]<=0) return 0;
        else return 100;
    }

    if (memo[conf[p-1]][conf[p]][p]>=0) 
        return memo[conf[p-1]][conf[p]][p];

    int ans=100;
    {
        int kmax=0,kmin=0;
        if (conf[p-1]>0) kmin=(conf[p-1]+b-1)/b; // ceil(conf[p-1]/b)
        if (conf[p]>0) kmax=(conf[p]+a-1)/a;
        if (conf[p-1]>0) chmax(kmax, (conf[p-1]+b-1)/b);
        if (conf[p+1]>0) chmax(kmax, (conf[p+1]+b-1)/b);
        assert(kmin<=kmax); //cout << p << ' ' << kmin << ' ' << kmax << endl; 

        for(int j=kmin; j<=kmax; ++j) {
            int a1 = conf[p-1], a2=conf[p], a3=conf[p+1];
            conf[p] = max(0,conf[p]-a*j);
            conf[p-1] = max(0,conf[p-1]-b*j);
            conf[p+1] = max(0,conf[p+1]-b*j);
            int curr = j+calc(conf,p+1);
            if (curr<ans) { ans=curr; best[a1][a2][p]=j; } // previously messed up a1,a2 with a2,a1
            conf[p-1]=a1; conf[p]=a2; conf[p+1]=a3;
        }
    }
    return memo[conf[p-1]][conf[p]][p]=ans;
}

void solve()
{
    memset(memo,-1,sizeof memo);
    memset(best,-1,sizeof best);
    cin >> n >> a >> b;
    VI h(n); for(int i=0; i<n; ++i) { cin >> h[i]; ++h[i]; } // add 1 to each h[i] since dead means h[i]<0

    int kans=calc(h,1); cout << kans << endl;
    VI ans;

    //for(int p1=0; p1<20; ++p1)
    //for(int p2=0; p2<20; ++p2)
    //    cout << best[p1][p2][1] << ' ' << memo[p1][p2][1] << endl;

    for(int i=1; i<n-1; ++i) {
        int k = best[h[i-1]][h[i]][i]; 
        h[i-1]=max(0,h[i-1]-b*k); 
        h[i]=max(0,h[i]-a*k); 
        h[i+1]=max(0,h[i+1]-b*k);
        for(int j=0; j<k; ++j) ans.PB(i+1);
    }
    for(int i=0; i<sz(ans); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}

int main()
{
    solve();
}

// a state is fully determined by 
// currpos, h[pos-1] and h[pos]
//
// for each pos in 1 to n-2
//   try all possible number of spells, min is to kill h[pos-1], max is to kill
//   h[pos+1]
//   recurse on pos+1 with new h[pos], h[pos+1]
//
//   550842     Jul 19, 2011 3:28:35 AM     lantimilan  D - Lizards and
//   Basements 2    GNU C++     Accepted    30 ms   1400 KB 
//
/* ***************
 *550822    Jul 19, 2011 2:10:01 AM     lantimilan  D - Lizards and Basements 2     GNU C++     Accepted    50 ms   20200 KB
 550820     Jul 19, 2011 1:50:32 AM     lantimilan  D - Lizards and Basements 2     GNU C++     Wrong answer on test 28     30 ms   2600 KB
 550819     Jul 19, 2011 1:43:32 AM     lantimilan  D - Lizards and Basements 2     GNU C++     Wrong answer on test 21     30 ms   2600 KB
 550783     Jul 19, 2011 12:17:55 AM    lantimilan  D - Lizards and Basements 2     GNU C++     Runtime error on test 16    30 ms   1400 KB
 550758     Jul 18, 2011 11:33:54 PM    lantimilan  D - Lizards and Basements 2     GNU C++     Wrong answer on test 21     30 ms   1400 KB
 550752     Jul 18, 2011 11:18:39 PM    lantimilan  D - Lizards and Basements 2     GNU C++     Memory limit exceeded on test 42    1970 ms     65500 KB
 550741     Jul 18, 2011 11:07:48 PM    lantimilan  D - Lizards and Basements 2     GNU C++     Wrong answer on test 23     30 ms   1400 KB
 550692     Jul 18, 2011 10:12:28 PM    lantimilan  D - Lizards and Basements 2     GNU C++     Memory limit exceeded on test 23    1950 ms     65500 KB
 550690     Jul 18, 2011 10:07:58 PM    lantimilan  D - Lizards and Basements 2     GNU C++     Wrong answer on test 1  30 ms   1400 KB
 550641     Jul 18, 2011 8:40:24 PM     lantimilan  D - Lizards and Basements 2     GNU C++     Wrong answer on test 99     30 ms   1400 KB
 550636     Jul 18, 2011 8:38:57 PM     lantimilan  D - Lizards and Basements 2     GNU C++     Wrong answer on test 21     30 ms   1400 KB
 550634     Jul 18, 2011 8:37:36 PM     lantimilan  D - Lizards and Basements 2     GNU C++     Wrong answer on test 1  10 ms   1400 KB 
 * */
