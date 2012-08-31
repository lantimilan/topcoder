// =========================================================
// 
//       Filename:  B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2011 08:14:02 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/08/2011, LI YAN
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
#define sz(x) int(x.size())

int cntbit(int n)
{
    int ans=0;
    while(n) { ++ans; n&=n-1; }
    return ans;
}
void solve()
{
    LL n; cin >> n;
    LL ans=100*n;
    for(int d=1; d<=5; ++d) { // d=four=seven
        int nd=2*d;
        for(int b=0; b<(1<<nd); ++b) {
            if (cntbit(b)!=d) continue;
            LL num=0;
            for(int x=0; x<nd; ++x) {
                if (b & 1<<x) num = num*10 + 7;
                else num = num*10 + 4;
            }
            if (num >= n) { ans=min(ans,num); }
        }
    }
    cout << ans << endl;
}

int main()
{
    solve();
}
