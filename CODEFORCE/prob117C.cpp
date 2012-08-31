// =========================================================
// 
//       Filename:  prob117C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/23/2011 09:35:37 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/23/2011, LI YAN
// 
// =========================================================
//
// tournament (graph theory)
// - if a tournament has a cycle, it has a triangle
// - a tournament always have a hamitonian path
// - if a tournament is strongly connected, then it has a hamitonial cycle
// - if a tournament is strongly connected, then for every vertex v
// for every l=3 to n, there is a cycle of length l containing v
// - if a tournament is 4-connected, every pair of vertices can be connected
// with a hamitonian path (Thomassen 1980)
// - if a tournament is acyclic, then the score sequence (outdeg) is
// 0,1,2,...,n-1

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

vector<int> mark;
vector<int> parent;
vector<string> adj;
vector<vector<int> > graph;

int cycle=-1;

void dfs(int k)
{
    mark[k]=1;
    //int n=int(adj.size());
    //for(int i=0; i<n; ++i) if (adj[k][i]=='1')
    for(int j=0; j<int(graph[k].size()); ++j)
    {
        int i=graph[k][j];
        if (mark[i]==0) { // tree edge
            parent[i]=k;
            dfs(i);
        }
        else if (mark[i]==1) { // back edge, found cycle
            if (cycle<0) cycle=k;
            return;
        }
        else {
            // forward edge or cross edge, do nothing
        }
    }
    mark[k]=2;
}

int main()
{
    int n; cin >> n; adj.resize(n);
    for(int i=0; i<n; ++i) 
    {
        char buf[5005]; scanf("%s",buf);
        adj[i]=buf;
    }

    graph.resize(n);
    for(int i=0; i<n; ++i)
    for(int j=0; j<n; ++j) if (adj[i][j]=='1')
        graph[i].push_back(j);

    mark.resize(n);
    parent.resize(n); fill(parent.begin(), parent.end(), -1);
    
    for(int i=0; i<n; ++i) 
        if (!mark[i] && cycle<0)
            dfs(i);
    
    if (cycle<0) { cout << -1 << endl; return 0; }

    vector<int> vec;
    int p;
    for(p=cycle; adj[cycle][p]!='1'; p=parent[p])
    { vec.push_back(p); }
    vec.push_back(p);

    reverse(vec.begin(),vec.end());
    // find triangle within cycle
    int ans[3]={-1};
    for(int k=2; k<int(vec.size()); ++k)
    {
        if (adj[vec[k]][vec[0]]=='1') {
            ans[0]=vec[0]; ans[1]=vec[k-1]; ans[2]=vec[k];
            break;
        }
    }
    
    cout << ans[0]+1 << ' ' << ans[1]+1 << ' ' << ans[2]+1 << endl;
}
