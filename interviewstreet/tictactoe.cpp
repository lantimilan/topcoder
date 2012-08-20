// =========================================================
// 
//       Filename:  tictactoe.cpp
// 
//    Description:  Summer Games
//
//         Challenges / Tic Tac Toe
// 
//        Version:  1.0
//        Created:  06/23/2012 03:41:57 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/23/2012, LI YAN
// 
// =========================================================

#include <iostream>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

const int N=3;

int board[N][N];

bool inbound(int r, int c)
{
    return 0<=r && r<N && 0<=c && c<N;
}

// return winpos for turn
// (-1,-1) if no winpos
pii findwin(int turn)
{
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
    if (board[i][j]==-1)
    {
        // check row
        bool win;
        win=true;
        for(int j2=0; j2<N; ++j2) {
            if (j!=j2 && board[i][j2]!=turn) 
                win=false;
        }
        if (win) return pii(i,j);
        win=true;
        // check col
        for(int i2=0; i2<N; ++i2) {
            if (i!=i2 && board[i2][j]!=turn)
                win=false;
        }
        if (win) return pii(i,j);
        // check NE diag
        if (i+j==N-1) {
        win=true;
        for(int i2=N-1, j2=0; i2>=0 && j2<N; i2--, j2++) {
            if (i!=i2 && j!=j2 && board[i2][j2]!=turn)
                win=false;
        }
        if (win) return pii(i,j);
        }
        // check NW diag
        if (i==j) {
        win=true;
        for(int i2=0, j2=0; i2<N && j2<N; i2++, j2++) {
            if (i!=i2 && j!=j2 && board[i2][j2]!=turn)
                win=false;
        }
        if (win) return pii(i,j);
        }
    }

    return pii(-1,-1);
}

int main()
{
    int turn; cin >> turn;
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
        cin >> board[i][j];

    
    int rr, cc;
    pii pos;
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j) 
    if (board[i][j]==-1) {
        if (rr<0) { rr=i; cc=j; }
        // S1: commit if win pos
        pos = findwin(turn);
        if (pos.first >=0) goto done;
        // S2: block if opponent has win pos
        pos = findwin(3-turn);
        if (pos.first >=0) goto done;
    }
    done:
    if (pos.first>=0) { 
        rr=pos.first; cc=pos.second;
    }
    cout << rr << ' ' << cc << endl;
}

// v2:
// take win pos if any, and block win pos of opponent
// v1: Sat Jun 23 21:16:06 PDT 2012
// no AI, just use the first available cell
