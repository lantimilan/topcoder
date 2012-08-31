// =========================================================
// 
//       Filename:  prob219D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/31/2012 01:16:17 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/31/2012, LI YAN
// 
// =========================================================
// cost[v] = forward[v] + backward_all - backward[v]

#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int> > adj;
vector<vector<int> > rev;
int vis[200000+10];
int backward[200000+10];
int path[200000+10];

void dfs(int s)
{
    vis[s] = 1;
    for(int i=0; i<(int)adj[s].size(); ++i) {
        int nb = adj[s][i];
        if (!vis[nb]) {
            path[nb] = path[s]+1;
            backward[nb] = backward[s];
            dfs(nb);
        }
    }
    for(int i=0; i<(int)rev[s].size(); ++i) {
        int nb = rev[s][i];
        if (!vis[nb]) {
            path[nb] = path[s]+1;
            backward[nb] = backward[s]+1;
            backward[0]++;
            dfs(nb);
        }
    }
}

int main()
{
    int n; scanf("%d", &n);
    adj.resize(n+1);
    rev.resize(n+1);
    for(int i=0; i<n-1; ++i) {
        int s, t; scanf("%d%d", &s, &t);
        adj[s].push_back(t);
        rev[t].push_back(s);
    }
    path[1] = 0;
    backward[0] = 0; // total backward edge in tree
    backward[1] = 0;
    dfs(1); // start at node[1]

    int best = n;
    vector<int> ans;
    for(int s=1; s<=n; ++s) {
        int cost = backward[0] + path[s] - 2*backward[s];
        if (cost < best) {
            best = cost;
            ans.clear(); ans.push_back(s);
        } else if (cost == best) {
            ans.push_back(s);
        }
    }
    printf("%d\n", best);
    for(int i=0; i<(int)ans.size(); ++i) {
        if (i) putchar(' ');
        printf("%d", ans[i]);
    }
    putchar('\n');
}
