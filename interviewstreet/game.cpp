// =========================================================
// 
//       Filename:  game.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/12/2012 06:34:45 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/12/2012, LI YAN
// 
// =========================================================

#include <iostream>
#include <vector>
using namespace std;

int gameResult(int a, int b)
{
    return a>b?a:b;
}

vector<int> game(int n) {

    vector<vector<int> > adj(n);
    vector<int> rank(n);
    vector<int> seen(n,0);
    vector<int> ans(n);

    for(int i=0; i<n; ++i)
    for(int j=i+1; j<n; ++j) {
        int a, b;
        a=b=0;
        for(int k=0; k<1000; ++k) {
            int res=gameResult(i, j);
            if (res==i) a++;
            else b++;
        }
        if (a>=b) adj[i].push_back(j);
        else adj[j].push_back(i);
    }
    for(int i=0; i<n; ++i) {
        int pos = n-1-adj[i].size();
        while(pos<n && seen[pos]) pos++;
        rank[i]=pos; seen[pos]=1;
    }
    for(int i=0; i<n; ++i) ans[rank[i]]=i;
    return ans;
}

int main()
{
    int n=100;
    vector<int> v=game(n);
    for(int i=0; i<n; ++i) cout << v[i] << ' ';
    cout << endl;
}
