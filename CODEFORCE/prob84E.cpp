// =========================================================
// 
//       Filename:  E.cpp
// 
//    Description:  E. Track
// 
//        Version:  1.0
//        Created:  05/13/2011 11:09:20 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/13/2011, LI YAN
// 
// =========================================================
//
// Two keys:
// 1. when gen comb, generate only those needed, here only need (26 choose 4)
// a saving from 1m to 6s by skiping many bfs calls
// 2. when in big loops, minimize expensive temp obj like string, vector
// a saving from 6s to 3s, string can be expensive when they are created and
// destroyed in big numbers

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

#define LMAX 2500
#define NARY 26

int NLETT;
string letters;
set<string> seen;
string bestpath;

string paths[60][60];
int dist[60][60]; 
int d1[60][60], d2[60][60];
int visit[60][60]; 

void checkmin(string& a, const string& b) 
{
    if (a.length() > b.length()) a=b;
    if (a.length()==b.length() && a>b) a=b;
}

bool hasnext(VI &alpha)
{
    if (!NLETT) return false;
    /*
    int carry=1;
    for(int i=0; i<int(alpha.size()); ++i)
    {
        alpha[i]+=carry; carry=alpha[i]/NLETT; alpha[i]%=NLETT; 
    }
    if (carry) return false;
    else return true;
    */
    int k=alpha.size();
    int p;
    for(p=k-1; p>=0; p--) {
        if (alpha[p]<NLETT+p-k) { alpha[p]++; break; }
    }
    if (p<0) return false;
    for(++p; p<k; ++p) alpha[p]=alpha[p-1]+1;
    return true;
}

// not used
void bfs(PII start, int n, int m, int usech[], const vector<string> &grid)
{
       for(int r=0; r<n; ++r) for(int c=0; c<m; ++c) dist[r][c] = LMAX;
       memset(visit, 0, sizeof visit);
       queue<PII> que; que.push(start); 
       visit[start.first][start.second]=1; dist[start.first][start.second]=0;
       while(!que.empty()) {
           PII pos = que.front(); que.pop(); 
           int r=pos.first, c=pos.second;
           int dir[][2] = {{-1,0},{0,+1}, {+1,0}, {0,-1}};
           for(int x=0; x<4; ++x)
           {
                int rr=r+dir[x][0], cc=c+dir[x][1];
                if (0<=rr && rr<n && 0<=cc && cc<m && !visit[rr][cc])
                {
                    visit[rr][cc]=1; dist[rr][cc] = dist[r][c]+1;
                    char ch = grid[rr][cc];
                    if (('a'<=ch && ch<='z' && usech[ch-'a']))
                    { que.push(PII(rr,cc)); }
                }
           }
       }
}

void updatepath(PII start, PII end, const vector<string> &grid, int usech[])
{
       int n=grid.size(), m=grid[0].size();
       //int len = d1[end.first][end.second];
       //string worst(len,'z');
       //if (len>=LMAX) return;
       //string worst(LMAX,'z');
       //for(int r=0;r<n;++r) for(int c=0;c<m;++c) paths[r][c]=worst;
       int len=LMAX;
       memset(visit, 0, sizeof visit);
       queue<PII> que; que.push(start); 
       int r=start.first, c=start.second;
       visit[r][c]=1; paths[r][c]=""; dist[r][c]=0;
       while(!que.empty()) {
           PII pos = que.front(); que.pop();
           r=pos.first, c=pos.second; if (d1[r][c]>=len) break;
           string snew = paths[r][c]+grid[r][c]; // this is a big saving, 4.894s to 3.086s
           int dir[][2] = {{-1,0},{0,+1}, {+1,0}, {0,-1}};
           for(int x=0; x<4; ++x)
           {
                int rr=r+dir[x][0], cc=c+dir[x][1];
                if (0<=rr && rr<n && 0<=cc && cc<m)
                {
                    if (!visit[rr][cc]) {
                        visit[rr][cc]=1; paths[rr][cc]=snew; 
                        dist[rr][cc]=dist[r][c]+1;
                        if (grid[rr][cc]=='T') len=dist[rr][cc];
                        char ch = grid[rr][cc];
                        if ('a'<=ch && ch<='z' && usech[ch-'a']) 
                            que.push(PII(rr,cc));
                    }
                    else { checkmin(paths[rr][cc],snew); }

                }
           }
       }
       if (visit[end.first][end.second])
           checkmin(bestpath, paths[end.first][end.second]);
}

void solve()
{
    int n,m,k; cin >> n >> m >> k;
    vector<string> grid(n);
    for(int i=0; i<n; ++i) cin >> grid[i];

    letters="";
    int choice[26]={0};
    PII start, end;
    for(int r=0; r<n; ++r) for(int c=0; c<m; ++c)
    {
        if (grid[r][c]=='S') start = PII(r,c);
        if (grid[r][c]=='T') end = PII(r,c);
        if ('a'<=grid[r][c] && grid[r][c]<='z')
            choice[grid[r][c]-'a']=1;
    }
    // one optimization here
    // generate comb only on the letters appeared in grid
    // seems less critical
    for(int i=0; i<26; ++i)
        if (choice[i]) letters+=char(i+'a');
    NLETT = letters.size();

    seen.clear();
    VI alpha(k); for(int i=0; i<k; ++i) alpha[i]=i;
    bestpath=string(LMAX,'z');
    do {
       // bfs with alpha
       int usech[26] = {0};
       for(int i=0; i<k; ++i) {
         char ch = letters[alpha[i]];
         usech[ch-'a']=1;
       }
       //string curr;
       //for(int i=0; i<26; ++i)
       //  if (usech[i]) curr+=char(i+'a');

       //if (curr.length() < min(size_t(k),letters.size())) continue;
       // this is the step to cut run time from 1m to 5s
       // by skiping combs already seen
       //if (seen.find(curr)!=seen.end()) continue;
       //else seen.insert(curr);

       //bfs(start,n,m,usech,grid); memcpy(d1,dist,sizeof dist);
       //bfs(end,n,m,usech,grid); memcpy(d2,dist,sizeof dist);
       updatepath(start, end, grid, usech);
       //cout << path << endl;
       //if (bestpath.length() > path.length() || 
       //     (bestpath.length()==path.length() && bestpath > path))
       //{ bestpath = path; }
       //cout << bestpath << endl;
    } while(hasnext(alpha));
    if (bestpath.length() >= LMAX) cout << "-1" << endl;
    else cout << bestpath.substr(1) << endl;
}

int main()
{
    solve();
}

// 456405   May 16, 2011 3:06:32 AM     lantimilan  E - Track   GNU C++
// Accepted     3050 ms     1800 KB
// 456403   May 16, 2011 3:04:03 AM     lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 12    5000 ms     1700 KB
// 456402   May 16, 2011 2:57:01 AM     lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 12    5000 ms     1700 KB
// 456399   May 16, 2011 2:45:07 AM     lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 12    5000 ms     1800 KB
// 456367   May 16, 2011 12:49:53 AM    lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 12    5000 ms     1800 KB
// 456345   May 16, 2011 12:25:26 AM    lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 12    5000 ms     1800 KB
// 456344   May 16, 2011 12:23:10 AM    lantimilan  E - Track   GNU C++
// Wrong answer on test 6   10 ms   1500 KB
// 456330   May 16, 2011 12:01:08 AM    lantimilan  E - Track   GNU C++
// Wrong answer on test 20  1940 ms     2600 KB
// 456323   May 15, 2011 11:44:47 PM    lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 12    5000 ms     1500 KB
// 455819   May 15, 2011 11:53:17 AM    lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 12    5000 ms     2000 KB
// 455809   May 15, 2011 11:35:13 AM    lantimilan  E - Track   GNU C++
// Runtime error on test 11     30 ms   1500 KB
// 455805   May 15, 2011 11:28:56 AM    lantimilan  E - Track   GNU C++
// Compilation error    0 ms    0 KB
// 455803   May 15, 2011 11:27:18 AM    lantimilan  E - Track   GNU C++
// Runtime error on test 11     10 ms   1500 KB
// 454500   May 14, 2011 9:53:51 AM     lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 12    5000 ms     2500 KB
// 454497   May 14, 2011 9:51:34 AM     lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 12    5000 ms     3100 KB
// 454474   May 14, 2011 9:31:16 AM     lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 8     5000 ms     3800 KB
// 454466   May 14, 2011 9:27:49 AM     lantimilan  E - Track   GNU C++     Time
// limit exceeded on test 8     5000 ms     3800 KB
// 454070   May 14, 2011 4:34:45 AM     lantimilan  E - Track   GNU C++
// Wrong answer on test 10  200 ms  1400 KB
// 454044   May 14, 2011 4:20:34 AM     lantimilan  E - Track   GNU C++
// Wrong answer on test 7   190 ms  1400 KB 
// [lyan@localhost CODEFORCE]$ time for ((i=1;i<=7;++i)); do ./a.out <E$i.in;
// done
// bcccc
// xxxx
// y
// -1
// aacccaa
// aab
// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
//
// real    0m10.428s
// user    0m10.236s
// sys     0m0.079s
//
// The following is WRONG
// the problem asks for a lexico minimum path, but it does not ask for 
// the exact seq of squares, so just maintain the letters appear in the path.
// in other words, as long as you know a prefix of abcddd, you do not care
// which seq of squares generated this prefix.
//
// It turns out that maintaining a path in each square is too slow.
//
// Sat May 14 00:15:41 PDT 2011
// run bfs for every comb of letters are just too slow
// time limit is 5s
//
// [lyan@localhost CODEFORCE]$ time ./a.out <E7.in 
// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
//
// real 1m6.053s
// user 1m5.144s
// sys  0m0.228s
//
