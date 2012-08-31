// =========================================================
// 
//       Filename:  Ex.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/30/2011 09:39:52 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/30/2011, LI YAN
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
#include <stack>
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

VI avail, best;

bool dfs(int maxdep, int depth, int n)
{
    if (depth > maxdep) return false;
    if (!best.empty()) return true;

    if (avail.back() == n) { 
        if (best.empty() || best.size() > avail.size()) best=avail;
        return true;
    }

    bool ans=false;
    for(int i=0; i<sz(avail); ++i)
    for(int j=0; j<sz(avail); ++j)
    for(int m=1; m<=8; m*=2)
    {
        int a = avail[i], b = avail[j];
        int c = a*m+b;
        if (avail.back()<c && c<=n) {
            avail.PB(c);   
            if (dfs(maxdep, depth+1, n)) ans=true;
            avail.pop_back();
        }
    }
    for(int i=0; i<sz(avail); ++i)
    for(int m=1; m<=8; m*=2)
    {
        int a = avail[i];
        int c = a*m;
        if (avail.back()<c && c<=n) {
            avail.PB(c);
            if (dfs(maxdep, depth+1, n)) ans=true;
            avail.pop_back();
        }
    }
    return ans;
}

void solve()
{
    int n; cin >> n;
    for(int d=0; d<10; ++d)
    {
    //cout << d << endl;
        avail.clear(); avail.PB(1);
        if (dfs(d,0,n)) break;
    }
    cout << best.size()-1 << endl;
    //for(int i=0; i<sz(best); ++i) cout << best[i] << " "; cout << endl;
    for(int i=1; i<sz(best); ++i)
    {
        string s1="eax", s2="eax", curr="eax";
        int a, m, b, c=best[i];
        int x,y; 
        for(x=i-1; x>=0; x--) for(y=i-1; y>=0; y--)
        {
            a=best[x]; b=best[y];
            for(m=1; m<=8; m*=2) { if (a*m+b==c) goto done; 
                if (a*m==c) { b=0; goto done; }
            }
        }
        done:
        s1[1] += x; s2[1] += y; curr[1] += i;
        string s = "lea " + curr + ", [";
        if (b) s += s2 + " + ";
        string num="012345678";
        if (m>1) { s += num[m]; s += "*"; }
        s += s1 + "]";
        cout << s << endl;
    }
}

int main()
{
    solve();
}
