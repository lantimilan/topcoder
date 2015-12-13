// flatland-roads.cpp
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <utility>
using namespace std;

const int K = 1e5;
int N, E, P;
vector<int> graph[K+5];
set<pair<int,int>> bridges;
int vis[K+5];
int parent[K+5];
int discover[K+5];
int low[K+5];

int C;
vector<int> supernodes[K+5];
set<int> superedges[K+5];
map<int,int> ver_comp;
int superparent[K+5];
// cnt of vertex reachable inside subtree, include subroot
int reach[K+5][20];
// cnt of vertex reachable in subtree and anscestors
int all[K+5][20];

map<int,int> cnts;

void chmin(int &a, int b) {
    if (a > b) a = b;
}

void dfs(int s) {
    vis[s] = 1;
    low[s] = discover[s];
    for (int next : graph[s]) if (!vis[next]) {
        parent[next] = s;
        discover[next] = discover[s]+1;
        dfs(next);
        chmin(low[s], low[next]);
    }
    for (int next : graph[s]) if (next != parent[s] && parent[next] != s) {
        // back edge
        chmin(low[s], discover[next]);
    }

    if (low[s] >= discover[s] && parent[s] != s) {  // parent[root] = root
        //cout << (s+1) << ": " << low[s] << ' ' << discover[s] << endl;
        bridges.insert(make_pair(s, parent[s]));
        bridges.insert(make_pair(parent[s], s));
        //cout << "bridge " << (s+1) << ' ' << parent[s]+1 << endl;
    }
}

void dfs_nobridge(int s, int comp) {
    vis[s] = 1;
    ver_comp[s] = comp; supernodes[comp].push_back(s);
    for (int next : graph[s])
        if (!vis[next])
        if (!bridges.count(make_pair(s, next))) {
        dfs_nobridge(next, comp);
    }
}

void dfs_tree(int c) {
    for (int next : superedges[c]) if (next != superparent[c]) {
        superparent[next] = c;
        dfs_tree(next);
    }
}

int calc(int c, int k) {
    if (k < 0) return 0;
    if (k == 0) return all[c][0] = reach[c][0] = supernodes[c].size();

    if (reach[c][k] > 0) return reach[c][k];

    reach[c][k] = supernodes[c].size();
    int pa = c;
    for (int next : superedges[c]) {
        if (superparent[next] == c) {
            reach[c][k] += calc(next, k-1);
        } else {
            pa = next;
        }
    }
    all[c][k] = reach[c][k];
    if (pa != c) {  // only root has parent being self
        //cout << "parent " << pa << ' ' << c << ' '
        //    << k << ' ' << all[pa][k-1] << endl;
        all[c][k] += all[pa][k-1] - calc(c, k-2);
    }
    //cout << "calc " << c << ' ' << k << ' ' << reach[c][k]
    //    << ' ' << all[c][k] << endl;
    return all[c][k];
}

int main() {
    cin >> N >> E >> P;
    for (int i = 0; i < E; ++i) {
        int u, v; cin >> u >> v;
        --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    discover[0] = 0;
    dfs(0);

    C = 0;
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < N; ++i) if (!vis[i]) {
        dfs_nobridge(i, C++);
    }

    /*
    for (int i = 0 ; i < N; ++i) {
        cout << (i+1) << ": comp " << ver_comp[i] << endl;
    }
    */

    for (int i = 0; i < N; ++i)
    for (int j : graph[i]) {
        int c1 = ver_comp[i];
        int c2 = ver_comp[j];
        if (c1 != c2) {
            superedges[c1].insert(c2);
            superedges[c2].insert(c1);
        }
    }

    /*
    for (int c = 0; c < C; ++c) {
        cout << "start " << c << ": ";
        for (int d : superedges[c]) {
            cout << d << ' ';
        } cout << endl;
    }
    */

    dfs_tree(0);

    /*
    for (int c = 0; c < C; ++c) {
        cout << "comp " << c << " -> parent " << superparent[c] << endl;
    }
    */

    memset(reach, 0, sizeof reach);
    for (int k = 0; k <= P; ++k) {
        for (int c = 0; c < C; ++c) {
            calc(c, k);
        }
    }
    /*
    for (int k = 1; k <= P; ++k)
    for (int c = 0; c < C; ++c) {
        cout << "reach " << c << ' ' << k << ": " << reach[c][k] << endl;
    }
    */

    for (int c = 0; c < C; ++c) {
        for (int vertex : supernodes[c]) {
            cnts[vertex] = all[c][P] - 1;  // subtract self
        }
    }

    for (auto &kv : cnts) {
        cout << kv.second << endl;
    }
}
