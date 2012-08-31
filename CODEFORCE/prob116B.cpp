// =========================================================
// 
//       Filename:  prob116B.cpp
// 
//    Description:  http://codeforces.com/contest/116/problem/B
// 
//        Version:  1.0
//        Created:  09/15/2011 01:32:50 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int n,m; cin >> n >> m;
    vector<string> mat(n);
    for(int i=0; i<n; ++i)
    {
        cin >> mat[i];
    }

    int ans=0;
    for(int i=0; i<n; ++i)
    for(int j=0; j<m; ++j)
    {
        if (mat[i][j]=='P') {
            int dx[] = {-1,0,+1,0};
            int dy[] = {0,+1,0,-1};
            for(int k=0;k<4;++k)
            {
                int ii=i+dx[k], jj=j+dy[k];
                if (0<=ii&&ii<n && 0<=jj&&jj<m && mat[ii][jj]=='W')
                { ans++; mat[ii][jj]='.'; }
            }
        }
    }
    cout << ans << endl;
}
