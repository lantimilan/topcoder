// =========================================================
// 
//       Filename:  prob110E.cpp
// 
//    Description:  http://codeforces.com/contest/110/problem/E
// 
//        Version:  1.0
//        Created:  09/16/2011 09:31:10 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/16/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

vector<vector<int> > graph;
map<pii,int> lucky;
vector<bool> visit;

bool islucky(int n)
{
    if (n==0) return false;
    while(n) {
        if (n%10==4 || n%10==7) {}
        else { return false; }
        n/=10;
    }
    return true;
}

int dfs(int v)
{
    int ans=1;
    visit[v]=true;
    for(int x=0; x<int(graph[v].size()); ++x)
    {
        int next = graph[v][x];
        if (!visit[next] && !lucky.count(pii(v,next)))
            ans+=dfs(next);
    }
    return ans;
}

int main()
{
    int n; cin >> n;
    graph.resize(n);
    for(int i=0; i<n-1; ++i)
    {
        int u,v,w; cin >> u >> v >> w; --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        if (islucky(w)) { 
            lucky[pii(u,v)]=lucky[pii(v,u)]=1;
        }
    }

    vector<int> parts;
    visit.resize(n);
    for(int i=0; i<n; ++i) if (!visit[i])
    {
        int k=dfs(i);
        parts.push_back(k);
    }

    long long ans=0LL;
    for(int i=0; i<int(parts.size()); ++i)
    {
        long long tmp=n-parts[i];
        ans += parts[i]*tmp*(tmp-1);
    }
    cout << ans << endl;
}

// 705473   Sep 16, 2011 8:50:39 PM     lantimilan  E - Lucky Tree  GNU C++
// Accepted     750 ms  13300 KB
// 705449   Sep 16, 2011 8:41:30 PM     lantimilan  E - Lucky Tree  GNU C++
// Wrong answer on test 12  30 ms   1400 KB 
//
// Algorithm:
// we need to count different triples with (i,j,k) and path(i,j) and path(i,k)
// have at least one lucky edge
//
// if we can count, for each i=0 to n-1, how many (i,j,k) for that fixed i, then
// we are done. To this end, we can do a bfs or dfs and stop when hit a lucky 
// edge. Nodes visited in this search cannot be j or k, and nodes unvisited can
// all be j or k. So for this i, we have count = unvisit*(unvisit-1)
// 
// Do this for all i=0 to n-1 is too slow, 10^5*10^5=10^10
// But if we look at the problem once more, suppose we partition nodes by
// removing all lucky edges, any two nodes in the same component cannot be in the 
// same triple because they do not have a lucky edge in between. On the other
// hand, every node inside a component and every node outside that component has
// a lucky edge in between. So we can count number of triples for all nodes in
// one partition as #part[i]*(#outside_part[i])*(#outside_part[i]-1) since we
// can choose one node from part[i] and 2 nodes from outside part[i]
