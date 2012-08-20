// =========================================================
// 
//       Filename:  hyperstring.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/15/2012 02:05:46 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/15/2012, LI YAN
// 
// =========================================================

#include <string>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int MOD=1000000000+7;
int N, M;
vector<string> dict;
int dp[105][105];

void refadd(int &a, int b)
{
    a=((int64)a+b)%MOD;
}

int main()
{
    cin >> N >> M;
    string word;
    for(int i=0; i<N; ++i) {
        cin >> word;
        dict.push_back(word);
    }
    dp[0][0]=1;
    for(int i=1; i<=N; ++i) {
        int l = dict[i-1].length();
        for(int j=0; j<=M; ++j)
        {
            refadd(dp[i][j], dp[i-1][j]);
            for(int k=1; j>=l*k; k++)
                refadd(dp[i][j], dp[i-1][j-l*k]);
        }
    }

    for(int i=1; i<=N; ++i) {
        for(int j=0; j<=M; ++j) cout << dp[i][j] << ' ';
        cout << endl;
    }
    int ans=0;
    for(int j=0; j<=M; ++j)
        refadd(ans, dp[N][j]);
    cout << ans << endl;
}

// no idea yet
