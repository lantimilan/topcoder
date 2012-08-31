// =========================================================
// 
//       Filename:  prob123C.cpp
// 
//    Description:  C. Brackets
// 
//        Version:  1.0
//        Created:  11/09/2011 09:21:49 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 11/09/2011, LI YAN
// 
// =========================================================

#include <cstring>
#include <iostream>
#include <map>
using namespace std;

typedef pair<int,int> pii;

int mat[105][105]; // 0 for lparen, 1 for rparen
int order[105][105]; // priority matrix
long long dp[105][105][205]; // row,col,lparen

map<int,pii> loc;

int n,m;
long long k;

long long
calc()
{
    memset(dp,0,sizeof dp);
    dp[0][0][1]=1LL;
    for(int i=0; i<n; ++i)   
    for(int j=0; j<m; ++j)
    for(int l=0; l<=m*n; ++l)
    {
        if (mat[i][j]==-1) {
            if (l>0) { // lparen
                if (i>0) dp[i][j][l]+=dp[i-1][j][l-1];
                if (j>0) dp[i][j][l]+=dp[i][j-1][l-1];
            }
            // rparen
            if (i>0) dp[i][j][l]+=dp[i-1][j][l+1];
            if (j>0) dp[i][j][l]+=dp[i][j-1][l+1];
        }
        else if (mat[i][j]==0) { // lparen
            if (l>0) { 
                if (i>0) dp[i][j][l]+=dp[i-1][j][l-1];
                if (j>0) dp[i][j][l]+=dp[i][j-1][l-1];
            }
        }
        else { // rparen
            if (i>0) dp[i][j][l]+=dp[i-1][j][l+1];
            if (j>0) dp[i][j][l]+=dp[i][j-1][l+1];
        }
    }
    return dp[n-1][m-1][0];
}

int main()
{
    cin >> n >> m >> k;

    for(int i=0; i<n; ++i)
    for(int j=0; j<m; ++j)
    {
        cin >> order[i][j]; order[i][j]--;
        loc[order[i][j]]=pii(i,j);
    }

    memset(mat,-1,sizeof mat);
    for(int x=0; x<m*n; ++x)
    {
        pii pos=loc[x];
        int r=pos.first, c=pos.second;
        mat[r][c]=0;
        long long cnt=calc(); cout << r << ' ' << c << ' ' << cnt << endl;
        if (cnt<k) {
            k-=cnt; mat[r][c]=1;
        }
    }
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
        {
            if (mat[i][j]==0) cout << '(';
            else cout << ')';
        }
        cout << '\n';
    }
}
