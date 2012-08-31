// =========================================================
// 
//       Filename:  prob5B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/14/2011 01:47:52 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/14/2011, LI YAN
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
    vector<string> vs;
    string s;
    int nmax=0;
    while(getline(cin,s)) {
        vs.PB(s); nmax=max(nmax, sz(s));
    }
    int nstar = nmax+2;
    cout << string(nstar,'*') << endl;
    bool left=true;
    for(int i=0; i<sz(vs); ++i) {
        cout << '*';
        int gap = nmax - sz(vs[i]);
        if (gap%2==0) {
            int pad = gap/2;
            cout << string(pad,' ') << vs[i] << string(gap-pad,' ');
        } else {
            if (left) { 
                int pad = gap/2;
                cout << string(pad,' ') << vs[i] << string(gap-pad,' '); 
                left=false; 
            }
            else {
                int pad = gap/2+1;
                cout << string(pad,' ') << vs[i] << string(gap-pad,' ');
                left=true;
            }
        }
        cout << '*' << endl;
    }
    cout << string(nstar,'*') << endl;
}

int main()
{
    solve();
}
