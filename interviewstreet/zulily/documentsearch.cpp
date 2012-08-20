// =========================================================
// 
//       Filename:  documentsearch.cpp
// 
//    Description:  LCS
// 
//        Version:  1.0
//        Created:  06/16/2012 11:09:10 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/16/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

typedef pair<int,int> pii;
int dp[2005][2005];

void chmin(int &a, int b)
{
    a=a<b?a:b;
}
void solve()
{
    string text, patt;
    getline(cin, text);
    getline(cin, patt);

    int i, j, l1, l2, score;
    i=j=0; l1=text.size(); l2=patt.size();
    score=0;

    for(; i<l1 && j<l2; )
        if (text[i]==patt[j]) { ++i; ++j; score++; }
        else ++i;
    if (score == 0) { puts("0 0"); return; }
    patt=patt.substr(0,score);
    l2=patt.size();

    for(i=0; i<=l1; ++i)
    for(j=0; j<=l2; ++j)
        dp[i][j]=5000;
    for(i=0; i<=l1; ++i)
        dp[i][0]=1;

    for(j=1; j<=l2; ++j)
    for(i=1; i<=l1; ++i)
    if (text[i-1]==patt[j-1])
    {
        dp[i][j]=dp[i-1][j-1];
        for(int k=0; k<i-1; ++k)
            chmin(dp[i][j], dp[k][j-1]+1);
    }
    int ans=dp[l1][l2];
    for(i=0; i<l1; ++i) chmin(ans, dp[i][l2]);
    printf("%d %d\n", score, ans);
}

int main()
{
    int T; cin >> T; cin.ignore(1024,'\n');
    while(T--)
        solve();
}
