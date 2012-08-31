// =========================================================
// 
//       Filename:  prob133D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/14/2011 10:37:50 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/14/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
#include <map>
#include <utility>
using namespace std;

char grid[60][60];
int conf[60][60][4][2]; // row,col,DP,CP

typedef pair<int,int> pii;
typedef pair<pii,pii> key;

map<int,key> mp;

int drow[] = { 0,+1, 0,-1};
int dcol[] = {+1, 0,-1, 0};

int main()
{
    int m, n; scanf("%d%d\n", &m, &n); 
    for(int i=0; i<m; ++i) {
        gets(grid[i]);
        //puts(grid[i]);
    }
    int nrow, ncol;
    nrow=m; ncol=strlen(grid[0]);

    key head;
    int looplen;

    memset(conf, -1, sizeof conf);
    int r=0, c=0, DP=0, CP=0; // right 0,1,2,3, left 0,1
    int cnt=0;
    mp[cnt]=key(pii(r,c),pii(DP,CP));
    conf[r][c][DP][CP]=cnt++; 
    while(true) {
        char color=grid[r][c];
        // move to next
        // move along DP
        while(true) {
            int rr=r+drow[DP], cc=c+dcol[DP];
            if (0<=rr && rr<nrow && 0<=cc && cc<ncol
                && grid[rr][cc]==color) {
                    r=rr; c=cc;
                }
            else { break; }
        }
        // move along CP
        int x=DP; 
        if (CP==0) x=(x-1+4)%4;
        else x=(x+1)%4;
        while(true) {
            int rr=r+drow[x], cc=c+dcol[x];
            if (0<=rr && rr<nrow && 0<=cc && cc<ncol
                && grid[rr][cc]==color) {
                    r=rr; c=cc;
                }
            else { break; }
        }
        int rr=r+drow[DP], cc=c+dcol[DP];
        if (0<=rr && rr<nrow && 0<=cc && cc<ncol
            && grid[rr][cc]!='0') {
                r=rr; c=cc; 
        }
        else { // hit black or out-of-bounds
            if (CP==0) { 
                CP=1-CP;
            }
            else {
                DP=(DP+1)%4;
                CP=1-CP;
            }
        }
        //printf("%d %d %c DP %d CP %d\n", r, c, grid[r][c], DP, CP);
        if (conf[r][c][DP][CP]>=0) { // found loop
            head.first.first=r; head.first.second=c;
            head.second.first=DP; head.second.second=CP;
            looplen=cnt-conf[r][c][DP][CP];
            //printf("loop %d at row %d col %d cnt %d\n", looplen, r, c, cnt);
            break; 
        }
        else {
            mp[cnt]=key(pii(r,c),pii(DP,CP));
            conf[r][c][DP][CP]=cnt++;
        }
    }
    int idx=conf[head.first.first][head.first.second][head.second.first][head.second.second];
    int index = (n-idx) % looplen + idx; //printf("index %d, n %d, idx %d\n", index, n, idx);
    key last=mp[index];
    int rlast=last.first.first, clast=last.first.second;
    //printf("%d %d\n", rlast, clast);
    //putchar(grid[rlast][clast]); puts("");
    char ans[2]={0};
    ans[0]=grid[rlast][clast];
    puts(ans);
}

// 955919   Dec 15, 2011 9:36:33 AM     lantimilan  D - Piet    GNU C++
// Accepted     30 ms   1500 KB
// 955876   Dec 15, 2011 9:08:02 AM     lantimilan  D - Piet    GNU C++
// Wrong answer on test 12  30 ms   1500 KB
// 955586   Dec 14, 2011 11:32:13 PM    lantimilan  D - Piet    GNU C++
// Wrong answer on test 5   30 ms   1500 KB 
