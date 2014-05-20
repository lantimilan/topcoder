// C.cpp
//
// linear time SCC
// ans = \Prod {# of min price vertex in that component}
//
// the implementation here is faulty, it passed a lot of test cases,
// until get caught by Case #71
// C.bad.in is a small testcase to fail this code, ans should be 6 for
// total cost
//
// my faulty idea is like this:
// start at some node s, do dfs,
// for all nodes found in this dfs, do dfs_mark on Greverse to find
// SCC, and the nodes are examined in dfspre order
// this is false, because the dfs tree in dfs_mark may contain more than
// one SCC, thanks to the cross edge from right to left, now left to
// right in Greverse
// The case that fails it then becomes apparent
// 1 -- 2
// 1 -- 3
// 3 -- 2
// my code will think 2 and 3 are in the same SCC

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int MX = 1e5 + 5;
int cost[MX];
int comp[MX];
int subgraph[MX];
int minnode;
int mincost;
vector<int> dfslist;


vector<vector<int> > graph;
vector<vector<int> > rev_graph;
map<int, pair<int, int> > comp_map;  // comp, (mincost, numnode)

void dfs(int start, int id)
{
    subgraph[start] = id;
    dfslist.push_back(start);
    for (int x = 0; x < graph[start].size(); ++x) {
        int next = graph[start][x];
        if (subgraph[next] < 0)
            dfs(next, id);
    }
}

void dfs_mark(int start, int id)
{
//    cout << "dfs_mark " << start << ' ' << cost[start] << endl;
    comp[start] = id;
    if (cost[start] < mincost) {
        mincost = cost[start];
        minnode = 1;
    } else if (cost[start] == mincost) {
        minnode++;
    }
    for (int x = 0; x < rev_graph[start].size(); ++x) {
        int next = rev_graph[start][x];
        if (subgraph[next] == subgraph[id] && comp[next] < 0)
            dfs_mark(next, id);
    }
}

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> cost[i];
    graph.resize(n);
    rev_graph.resize(n);
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int u, w; cin >> u >> w;
        --u; --w;
        graph[u].push_back(w);
        rev_graph[w].push_back(u);
    }
    const int MOD = 1e9+7;
    long long money = 0;
    int ans = 1;
    memset(subgraph, -1, sizeof subgraph);
    memset(comp, -1, sizeof comp);
    for (int i = 0; i < n; ++i) if (subgraph[i] < 0) {
        dfslist.clear();
        dfs(i, i);
        for (int x = 0; x < dfslist.size(); ++x) {
            int next = dfslist[x];
            if (comp[next] < 0) {
                //mincost = 1<<30; minnode = 0;
                dfs_mark(next, next);
                //assert(mincost < (1<<30) && minnode > 0);
                //money += mincost;
                //ans = (long long)ans * minnode % MOD;
            }
        }
    }
    comp_map.clear();
    for (int i = 0; i < n; ++i) {
        int c = comp[i];
        if (comp_map.count(c)) {
            int mincost = comp_map[c].first;
            int numnode = comp_map[c].second;
            if (cost[i] < mincost) {
                comp_map[c] = make_pair(cost[i], 1);
            } else if (cost[i] == mincost) {
                comp_map[c].second++;
            }
        } else {
            comp_map[c] = make_pair(cost[i], 1);
        }
    }
    map<int, pair<int,int> >::iterator it;
    for (it = comp_map.begin(); it != comp_map.end(); ++it) {
        int mincost = it->second.first;
        int numnode = it->second.second;
        ans = (long long)ans * numnode % MOD;
        money += mincost;
    }
    cout << money << ' ' << ans << endl;
}
