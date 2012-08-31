// =========================================================
// 
//       Filename:  prob74C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  04/15/2011 08:01:52 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/15/2011, LI YAN
// 
// =========================================================
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> PII;

int n,m; // r < n and c < m
int total;
int vmap[1000000+3][4];

bool good(int r, int c) { return 0<=r && r<n && 0<=c && c<m; }
PII getid(int r, int c)
{ 
    if (r==0)   return PII(0,c);
    if (r==n-1) return PII(1,c);
    if (c==0)   return PII(2,r);
    if (c==m-1) return PII(3,r);
    assert(false);
    return PII(0,0);
}
void check(int r, int c)
{
    PII id = getid(r,c);
    if (vmap[id.first][id.second]) return;

    cout << "check " << r << " " << c 
        << "\t" << id.first << " " << id.second << endl;

    vmap[id.first][id.second] = total;
    int dir[4][2] = {{-1,-1}, {-1,+1}, {+1,+1}, {+1,-1}};
    int dest[4][2] = {{0,0}, {0,m-1}, {n-1,m-1}, {n-1,0}};

    for(int k=0; k<4; ++k) {
        int diff = min(abs(dest[k][0]-r), abs(dest[k][1]-c));
        int rr = r+dir[k][0]*diff; 
        int cc = c+dir[k][1]*diff;
        cout << rr << " " << cc << endl;
        assert(good(rr,cc));
        check(rr,cc);
    }
}

void solve()
{
    cin >> n >> m;
    total = 0;
    int r,c;
    r=0; for(c=0; c<m; ++c) 
    {   PII id = getid(r,c); 
        if (!vmap[id.first][id.second]){ cout << "** " << r << " " << c << endl; ++total; check(r,c); } 
    }
    r=n-1; for(c=0; c<m; ++c)
    {   PII id = getid(r,c); 
        if (!vmap[id.first][id.second]){ cout << "** " << r << " " << c << endl; ++total; check(r,c); } 
        //if (!vmap[id.first][id.second]){ ++total; check(r,c); } 
    }
    c=0; for(r=0; r<n; ++r)
    {   PII id = getid(r,c); 
        if (!vmap[id.first][id.second]){ cout << "** " << r << " " << c << endl; ++total; check(r,c); } 
        //if (!vmap[id.first][id.second]){ ++total; check(r,c); } 
    }
    c=m-1; for(r=0; r<n; ++r)
    {   PII id = getid(r,c); 
        if (!vmap[id.first][id.second]){ cout << "** " << r << " " << c << endl; ++total; check(r,c); } 
        //if (!vmap[id.first][id.second]){ ++total; check(r,c); } 
    }

    cout << total << endl;
}
int main()
{
    solve();
}
