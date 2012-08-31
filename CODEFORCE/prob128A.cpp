// =========================================================
// 
//       Filename:  prob128A.cpp
// 
//    Description:  http://codeforces.com/contest/128/problem/A
// 
//        Version:  1.0
//        Created:  11/15/2011 09:17:09 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 11/15/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
    char board[10][10];
    for(int i=0; i<8; ++i)
    {
        gets(board[i]);
    }

    int mark[10][10]; memset(mark,0,sizeof mark);
    mark[7][0]=1;
    while(true)
    {
        // Maria move
        for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
        if (mark[i][j]==1)
        {
            assert(board[i][j]!='S');
            int dx[]={-1,-1,-1, 0, 0,+1,+1,+1};
            int dy[]={-1, 0,+1,-1,+1,-1, 0,+1};
            for(int k=0; k<8; ++k)
            {
                int r=i+dx[k], c=j+dy[k];
                if (0<=r && r<8 && 0<=c && c<8 
                    && mark[r][c]!=1 && board[r][c]!='S')
                {
                    mark[r][c]=2;
                }
            }
        }
        for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
        {
            if (mark[i][j]) mark[i][j]=1;
        }
        if (mark[0][7]) break;

        // Statue move
        char newboard[10][10]; memset(newboard,0,sizeof newboard);
        for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
            newboard[i][j]='.';

        for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
        if (board[i][j]=='S') {
            if (i+1<8) newboard[i+1][j]='S';
        }
        memcpy(board,newboard,sizeof board);
        for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
        if (board[i][j]=='S') {
            mark[i][j]=0;
        }
        bool good=false;
        for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
        if (mark[i][j]) good=true;

        if (!good) break;
    }
    if (mark[0][7]) puts("WIN");
    else puts("LOSE");
}
