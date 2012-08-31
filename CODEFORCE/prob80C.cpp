// =========================================================
// 
//       Filename:  prob69C.cpp
// 
//    Description:  Heroes
// 
//        Version:  1.0
//        Created:  04/19/2011 11:01:40 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/19/2011, LI YAN
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

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

int max3(int a, int b, int c) { return max(a, max(b,c)); }
int min3(int a, int b, int c) { return min(a, min(b,c)); }

int countbit(int n)
{
    int ans=0;
    while(n) { ans++; n&=n-1; }
    return ans;
}

void solve()
{

    map<string,int> heroes;
    const char* names[] = {"Anka", "Chapay", "Cleo", "Troll", "Dracul", "Snowy", "Hexadecimal"};
    for(int i=0; i<int(sizeof(names)/sizeof(names[0])); ++i) heroes[names[i]] = i;

    int likes[10][10]; memset(likes,0,sizeof likes);
    int n; cin >> n;
    for(int i=0; i<n; ++i)
    {
        string a, b; cin >> a; cin >> b >> b;
        likes[heroes[a]][heroes[b]] = 1;
    }
    int expn = 0, anslike=0;
    int abc[3]; for(int i=0; i<3; ++i) { cin >> abc[i]; expn = max(expn, abc[i]); }
    int g[3], assign[3];
    for(g[0]=1; g[0]<7; ++g[0]) for(g[1]=1; g[0]+g[1]<7; ++g[1])
    {
        g[2] = 7-g[0]-g[1];
        int currmax = max3(abc[0]/g[0], abc[1]/g[1], abc[2]/g[2]);
        int currmin = min3(abc[0]/g[0], abc[1]/g[1], abc[2]/g[2]);
        int diff = currmax - currmin; assert(diff >= 0);
        if (diff > expn) continue;
        if (diff < expn) anslike = 0;
        expn = diff; for(int i=0; i<3; ++i) assign[i] = g[i]; 
        
        // now assign names to assign[]
        int maxlike = 0; int b[3];
        for(b[0]=0; b[0]<(1<<7); ++b[0]) if (countbit(b[0])==assign[0])
        for(b[1]=0; b[1]<(1<<7); ++b[1]) if ((b[0]&b[1])==0 && countbit(b[1])==assign[1])
        {
            int curr = 0;
            b[2] = ((1<<7)-1) & ~(b[0]|b[1]); assert(countbit(b[2])==assign[2]);
            for(int i=0; i<3; ++i)
            {
                for(int k1=0; k1<7; ++k1) for(int k2=0; k2<7; ++k2)
                if ((1<<k1 & b[i]) && (1<<k2 & b[i]) && likes[k1][k2]) ++curr;
            }
            //if (maxlike < curr) { cout << b[0] << " " << b[1] << " " << b[2] << endl; }
            maxlike = max(maxlike, curr);
        }
        anslike = max(anslike, maxlike);

    }
    cout << expn << " " << anslike << "\n";
}

int main()
{
    solve();
}

/***************
 * 402072        Apr 19, 2011 10:56:04 PM   lantimilan        77A - Heroes
 * GNU C++       Wrong answer on test 61     30 ms       1400 KB 
 */
