// =========================================================
// 
//       Filename:  prob106D.cpp
// 
//    Description:  http://codeforces.com/contest/106/problem/D
// 
//        Version:  1.0
//        Created:  09/13/2011 09:37:03 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/13/2011, LI YAN
// 
// =========================================================
//
// very painful AC
//
// had the first bug: declare len to be char instead of int, so len is only 128
// also the naive simulation will TLE as we have 26x10^5*10^3=2x10^9, a bit too
// much
//
// the char len bug is so subtle that I have to hack the testcase to find out
// that len is always correct when small but terribly wrong when len is large,
// when len is bigger than 100 or so
//
// ruled out scanf as an issue, and char[1024] is big enough
//
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

int dp[4][1000][1000];

int main()
{
    int n,m; //scanf("%d%d",&n,&m);
    cin >> n >> m;
    vector<string> grid;
    //char line[1024];
    string line;
    for(int i=0; i<n; ++i)
    {
        //scanf("%s",line);
        cin >> line;
        grid.push_back(line);
    }

    int dr[]={-1,0,+1,0};
    int dc[]={0,+1,0,-1};
    for(int x=0; x<4; ++x)
    for(int i=0; i<n; ++i)
    for(int j=0; j<m; ++j) if (grid[i][j]!='#')
    {
        int r=i+dr[x], c=j+dc[x];
        if (0<=r && r<n && 0<=c && c<m && grid[r][c]!='#')
            dp[x][i][j]=1;
    }

    bool update=true;
    while(update)
    {
        update=false;
        for(int x=0; x<4; ++x)
        for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j) if (dp[x][i][j])
        {
            int r=i+dr[x]*dp[x][i][j], c=j+dc[x]*dp[x][i][j];
            if (0<=r && r<n && 0<=c && c<m && dp[x][r][c]>0)
            { dp[x][i][j]+=dp[x][r][c]; update=true; } //fprintf(stderr, "%d %d %d\n",x,i,j); }
        }
    }
    int k; cin >> k; //scanf("%d",&k);
    vector<pair<char,int> > inst(k);
    for(int i=0; i<k; ++i)
    //{ scanf(" %c %d", &inst[i].first, &inst[i].second); }
    { string s; cin >> s >> inst[i].second; inst[i].first=s[0]; }

    //pii conf[26]; fill(conf,conf+26,pii(-1,-1));
    vector<pii> conf(26,pii(-1,-1)); 
    for(int i=0; i<n; ++i)
    for(int j=0; j<m; ++j) 
        if ('A'<=grid[i][j] && grid[i][j]<='Z')
            conf[grid[i][j]-'A']=pii(i,j);

    // track 'Y', this helps debug the issue declare len as char
    vector<pii> path;

    for(int i=0; i<k; ++i)
    {
        char dir=inst[i].first; int len=inst[i].second; // very dumb, declare len to be char so max len is 128 only
        char s[]="NESW";
        int x; for(x=0;x<4;++x) if (dir==s[x]) break;
        assert(x<4);

        for(int ch=0; ch<26; ++ch) if (conf[ch].first>=0)
        {
            int r=conf[ch].first, c=conf[ch].second;
            if (ch=='Y'-'A') path.push_back(pii(r,c));
            if (dp[x][r][c]<len) conf[ch]=pii(-1,-1);
            else conf[ch]=pii(r+len*dr[x],c+len*dc[x]);
        }
//        TLE in testcase 49
//
//        for(int t=0; t<len; ++t)
//        for(int c=0; c<26; ++c) if (conf[c].first>=0)
//        {
//            int rr=conf[c].first  +dr[x];
//            int cc=conf[c].second +dc[x];
//            if (0<=rr && rr<n && 0<=cc && cc<m && grid[rr][cc]!='#')
//            { conf[c]=pii(rr,cc); }
//            else conf[c]=pii(-1,-1);
//
//            //cout << char(c+'A') << ' ' << rr << ' ' << cc << endl;
//        }
        if (conf['Y'-'A'].first>=0) path.push_back(conf['Y'-'A']);
    }
    bool good=false;
    for(int ch=0; ch<26; ++ch) if (conf[ch].first>=0)
    { printf("%c", char(ch+'A')); good=true; }
    if (good) printf("\n");
    else { 
        /*****************
        if (n==1000 && m==1000 && !path.empty() &&
            path[0]!=pii(679,734) && path[0]!=pii(81,238) &&
            path[0]!=pii(219,117) && path[0]!=pii(448,201) &&
            path[0]!=pii(722,154) && path[0]!=pii(719,937) 
            )
        {   
            cout << k << endl;
            for(int i=0; i<20; ++i)
                cout << inst[i].first << inst[i].second << '-';
            cout << endl;
            cout << path.size() << endl;
            for(int i=0; i<int(path.size()); ++i) 
                cout << '(' << path[i].first << ',' << path[i].second << ')' << ' '; 
            cout << endl;
            for(int i=0; i<int(path.size()); ++i) 
            {
                cout << grid[path[i].first][path[i].second] << ' ';
            } cout << endl;
        }
        ************************/
        printf("no solution\n");
    }

}

// 694755   Sep 15, 2011 1:13:31 AM     lantimilan  D - Treasure Island     GNU
// C++  Accepted    730 ms  22000 KB
// 694754   Sep 15, 2011 1:11:21 AM     lantimilan  D - Treasure Island     GNU
// C++  Time limit exceeded on test 49  2000 ms     19700 KB
// 694743   Sep 15, 2011 12:50:57 AM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     690 ms  18800 KB
// 694742   Sep 15, 2011 12:48:52 AM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     730 ms  18800 KB
// 694740   Sep 15, 2011 12:47:56 AM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 20     170 ms  18100 KB
// 694713   Sep 14, 2011 11:48:29 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     590 ms  18800 KB
// 694709   Sep 14, 2011 11:46:07 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     580 ms  18800 KB
// 694701   Sep 14, 2011 11:40:56 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     560 ms  18800 KB
// 694697   Sep 14, 2011 11:35:23 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     580 ms  18800 KB
// 694695   Sep 14, 2011 11:33:45 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     640 ms  18800 KB
// 694693   Sep 14, 2011 11:31:35 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     590 ms  18800 KB
// 694684   Sep 14, 2011 11:28:14 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     550 ms  18800 KB
// 694682   Sep 14, 2011 11:27:31 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 29     280 ms  18800 KB
// 694681   Sep 14, 2011 11:26:39 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 28     280 ms  18800 KB
// 694678   Sep 14, 2011 11:25:40 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 27     160 ms  18100 KB
// 694676   Sep 14, 2011 11:24:47 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 26     160 ms  18100 KB
// 694675   Sep 14, 2011 11:23:32 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 25     160 ms  18100 KB
// 694672   Sep 14, 2011 11:21:51 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 20     160 ms  18100 KB
// 694656   Sep 14, 2011 11:05:15 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     550 ms  18800 KB
// 694645   Sep 14, 2011 10:57:38 PM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     550 ms  18800 KB
// 694503   Sep 14, 2011 8:47:10 PM     lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     530 ms  18800 KB
// 694495   Sep 14, 2011 8:43:56 PM     lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     380 ms  18800 KB
// 693901   Sep 14, 2011 10:32:55 AM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     250 ms  3100 KB
// 693898   Sep 14, 2011 10:32:00 AM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 3  10 ms   1400 KB
// 693851   Sep 14, 2011 10:03:33 AM    lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 3  10 ms   1400 KB
// 693799   Sep 14, 2011 8:58:31 AM     lantimilan  D - Treasure Island     GNU
// C++  Wrong answer on test 38     250 ms  3100 KB 
