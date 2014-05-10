// C.cpp
//
// linear time SCC
// ans = \Prod {# of min price vertex in that component}

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int MX = 1e5 + 5;
int cost[MX];
int dfspre[MX];
int dfspost[MX];
int comp[MX];
int gclock;
pair<int,int> nodepair[MX];

vector<vector<int> > graph;
vector<vector<int> > rev_graph;
map<int, pair<int, int> > comp_map;  // compid, (cost, cnt)

void dfs(int start)
{
    dfspre[start] = gclock++;
    for (int x = 0; x < graph[start].size(); ++x) {
        int next = graph[start][x];
        if (dfspre[next] < 0)
            dfs(next);
    }
    dfspost[start] = gclock++;
}

void dfs_mark(int start, int id)
{
    comp[start] = id;
    for (int x = 0; x < rev_graph[start].size(); ++x) {
        int next = rev_graph[start][x];
        if (dfspre[id] < dfspre[next] && dfspost[id] > dfspost[next])
        if (comp[next] < 0)
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
    memset(dfspre, -1, sizeof dfspre);
    gclock = 0;
    for (int i = 0; i < n; ++i) if (dfspre[i] < 0)
        dfs(i);

//    for (int i = 0; i < n; ++i)
//        cout << i << ' ' << dfspre[i] << endl;

    for (int i = 0; i < n; ++i)
        nodepair[i] = make_pair(dfspre[i], i);
    sort(nodepair, nodepair+n);

    memset(comp, -1, sizeof comp);
    for (int x = 0; x < n; ++x) {
        int id = nodepair[x].second;
        if (comp[id] >= 0) continue;
        dfs_mark(id, id);
    }
//    for (int i = 0; i < n; ++i)
//        cout << i << ' ' << comp[i] << endl;

    for (int i = 0; i < n; ++i) {
        int cc = comp[i];
        if (comp_map.count(cc)) {
            int mincost = comp_map[cc].first;
            if (cost[i] < mincost)
                comp_map[cc] = make_pair(cost[i], 1);
            else if (cost[i] == mincost)
                comp_map[cc].second++;
        } else {
            comp_map[cc] = make_pair(cost[i], 1);
        }
    }

    const int MOD = 1e9+7;
    long long money = 0;
    int ans = 1;
    map<int, pair<int, int> >::iterator it;
    for (it = comp_map.begin(); it != comp_map.end(); ++it) {
        money += it->second.first;
        int cnt = it->second.second;
        ans = (long long) ans * cnt % MOD;
    }
    cout << money << ' ' << ans << endl;
}

