// =========================================================
// 
//       Filename:  prob77D.cpp
// 
//    Description:  D. Domino Carpet
// 
//        Version:  1.0
//        Created:  04/20/2011 12:26:35 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/20/2011, LI YAN
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

#define MOD 1000000007
int dp[300];
int carpet[300][300];

// 1: hori piece
// 2: vert piece
// 3: both
void parse(int n, int m)
{
    for(int r=0; r<n; ++r)
    {
        string lines[4];
        for(int i=0; i<4; ++i) getline(cin,lines[i]);
        //for(int i=0; i<4; ++i) cout << "line " << lines[i] << endl;
        for(int k=0; k < m; k++)
        {
            int cnt=0;
            for(int s=1; s<=3; s++) for(int t=1; t<=3; t++)
                cnt += (lines[s][4*k+t]=='O');
            //cout << r << " " << k << " " << cnt << endl;
            switch(cnt) {
            case 0: case 1: case 4: case 5: carpet[r][k] = 3; break;
            case 2: case 3: 
                if (lines[1][4*k+1]=='O') carpet[r][k] = 1;
                else carpet[r][k] = 2;
                break;
            case 6: 
                if (lines[1][4*k+2]=='O') carpet[r][k] = 1;
                else carpet[r][k] = 2;
                break;
            default: assert(false);
            }
        }
    }
}

bool isvert(int r, int c)
{ return (carpet[r][c] & 2) != 0; }

bool ishori(int r, int c)
{ return (carpet[r][c] & 1) != 0; }

void solve()
{
    memset(dp,0,sizeof dp);
    int n,m; cin >> n >> m; cin.ignore(1024,'\n');
    parse(n,m);

//    for(int r=0; r<n; ++r)
//    { for(int c=0; c<m; ++c) cout << carpet[r][c] << " "; cout << endl;}

    dp[0] = 1;
    for(int c=1; c<=m; ++c)
    {
        dp[c]=0;
        bool allvert = true;
        for(int r=1; r<=n; ++r) if (!isvert(r-1,c-1))
        { allvert=false; break; }
        if (n%2==0 && allvert) dp[c] += dp[c-1];
        if (c<2) continue;
        int dp2[300]; dp2[0]=1;
        for(int r=1; r<=n; ++r)
        {
            dp2[r] = 0;
            if (ishori(r-1,c-2) && ishori(r-1,c-1)) dp2[r] += dp2[r-1];
            if ( r>=2 && isvert(r-2,c-2) && isvert(r-2,c-1) && 
                isvert(r-1,c-2) && isvert(r-1,c-1))
                { dp2[r] = ((LL)dp2[r]+dp2[r-2])%MOD; }
            //cout << "r " << r << " " << dp2[r] << endl;
        }
        //cout << dp2[n] << endl;
        dp[c] = (dp[c]+(LL)dp2[n]*dp[c-2])%MOD;
        if (c>=2)
        {
            bool allvert = true;
            for(int r=1; r<=n; ++r) if (!(isvert(r-1,c-2) && isvert(r-1,c-1)))
            { allvert=false; break; }
            if (allvert && n%2==0) dp[c]=((LL)dp[c]-dp[c-2]+MOD)%MOD;
        }
        //cout << c << " " << dp[c] << endl;
    }
    cout << dp[m] << endl;
}

int main()
{
    solve();
}

/* **************
 * 404109   Apr 21, 2011 1:38:36 AM     lantimilan  77D - Domino Carpet     GNU
 * C++  Accepted    130 ms  1700 KB
 * 404108   Apr 21, 2011 1:27:16 AM     lantimilan  77D - Domino Carpet     GNU
 * C++  Wrong answer on test 4  10 ms   1700 KB 
 * */
