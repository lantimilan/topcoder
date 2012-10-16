// =========================================================
// 
//       Filename:  prob234F.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/16/2012 01:01:09 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/16/2012, LI YAN
// 
// =========================================================

#include <cstring>
#include <fstream>
using namespace std;

int dp[205][40000+5][2]; // pos, red, last
int ht[205];
int pre[205];

void update(int &x, int y)
{
    if (x<0) x = y;
    if (y>=0) x = min(x,y);
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n; fin >> n;
    int a, b; fin >> a >> b;
    int sum;

    sum = 0;
    ht[0] = pre[0] = 0;
    for(int i=1; i<=n; ++i) {
        fin >> ht[i];
        pre[i] = pre[i-1] + ht[i];
        sum += ht[i];
    }

    memset(dp, -1, sizeof dp);
    dp[0][0][0] = dp[0][0][1] = 0;
    for(int i=1; i<=n; ++i) {
        for(int h=0; h<=sum; ++h) // amount of red used, red is 0
        if (h<=a && pre[i]-h <= b)
        {
        int c1, c2;
        c1 = c2 = 0; // use red for ht[i] and ht[i-1] is red
        if (h >= ht[i] && dp[i-1][h-ht[i]][0] >= 0) {
            int curr = dp[i-1][h-ht[i]][0];
            update(dp[i][h][0], curr);
        }
        c1 = 0; c2 = 1; // use red for ht[i] and ht[i-1] is green
        if (h >= ht[i] && dp[i-1][h-ht[i]][1] >= 0) {
            int curr = dp[i-1][h-ht[i]][1] + min(ht[i-1], ht[i]);
            update(dp[i][h][0], curr);
        }
        c1 = 1; c2 = 0; // use green for ht[i] and ht[i-1] is red
        if (dp[i-1][h][0] >= 0) {
            int curr = dp[i-1][h][0] + min(ht[i-1], ht[i]);
            update(dp[i][h][1], curr);

        }
        c1 = 1; c2 = 1; // use green for ht[i] and ht[i-1] is green
        if (dp[i-1][h][1] >= 0) {
            int curr = dp[i-1][h][1];
            update(dp[i][h][1], curr);
        }
        }
    }

    int ans = -1;
    for(int h=0; h<=sum; ++h) {
        if (dp[n][h][0]>=0) update(ans, dp[n][h][0]);
        if (dp[n][h][1]>=0) update(ans, dp[n][h][1]);
    }
    fout << ans << endl;
}

// Accepted
