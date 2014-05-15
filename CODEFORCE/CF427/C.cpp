// C.cpp
//
// linear time SCC
// ans = \Prod {# of min price vertex in that component}
//
// SCC using two dfs
// 1. dfs on G to get finish time of each node
// 2. compute Grev
// 3. dfs on Grev, process node in the reverse order of finish time
// that is, last finished node processed first
// 4. each dfs tree in step 3 is a component

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
int vis[MX];
int minnode;
int mincost;
vector<int> dfslist;


vector<vector<int> > graph;
vector<vector<int> > rev_graph;
map<int, pair<int, int> > comp_map;  // comp, (mincost, numnode)

void dfs(int start)
{
    vis[start] = 1;
    for (int x = 0; x < graph[start].size(); ++x) {
        int next = graph[start][x];
        if (!vis[next]) dfs(next);
    }
    dfslist.push_back(start);
}

void dfs_mark(int start, int id)
{
    comp[start] = id;
    /*
    if (cost[start] < mincost) {
        mincost = cost[start];
        minnode = 1;
    } else if (cost[start] == mincost) {
        minnode++;
    }
    */
    for (int x = 0; x < rev_graph[start].size(); ++x) {
        int next = rev_graph[start][x];
        if (comp[next] < 0) dfs_mark(next, id);
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
    memset(vis, 0, sizeof vis);
    memset(comp, -1, sizeof comp);

    // dfs on G to compute finish time
    // nodes appended to dfslist in order of finish time
    for (int i = 0; i < n; ++i) if (!vis[i]) {
        dfs(i);
    }
    assert(dfslist.size() == n);

    // dfs on Grev, every dfs tree is a component
    for (int i = n-1; i >= 0; --i) {
        int node = dfslist[i];
        if (comp[node] < 0) dfs_mark(node, node);
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

