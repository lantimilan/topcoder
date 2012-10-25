// =========================================================
// 
//       Filename:  prob237B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/25/2012 08:40:23 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/25/2012, LI YAN
// 
// =========================================================

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;
int val[60][60];
int cnt[60];
vector<pair<pii,pii> > vec;

int main()
{
    int n; cin >> n;
    int sum=0;
    for(int i=0; i<n; ++i)
    {
        cin >> cnt[i];
        sum += cnt[i];
    }
    for(int i=0; i<n; ++i)
    for(int j=0; j<cnt[i]; ++j)
        cin >> val[i][j];

    int i, j;
    i=j=0;
    for(int k=1; k<=sum; ++k) {
        int x, y;
        for(x=0; x<n; ++x)
        for(y=0; y<cnt[x]; ++y)
            if (val[x][y] == k)
                goto done;
        done:
        if (x == i && y == j) {}
        else
        {
            int t = val[i][j];
            val[i][j] = val[x][y];
            val[x][y] = t;
            vec.push_back(make_pair(pii(i,j), pii(x,y)));
        }
        j++; if (j>= cnt[i]) { i++; j=0; }
    }
    cout << vec.size() << endl;
    for(int i=0; i<(int)vec.size(); ++i) {
        cout << vec[i].first.first + 1 << ' '
             << vec[i].first.second + 1 << ' '
             << vec[i].second.first + 1 << ' '
             << vec[i].second.second + 1 << endl;
    }
}
