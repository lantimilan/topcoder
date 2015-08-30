// prob574E.cpp
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// root arbitrarily
// recurse into subtrees
// if root deg <= 2, then good
// else root deg >= 3, then all but two subtrees must be deg <2 subtree

vector<int> graph[100000+5];
int vis[100000+5];

// Returns a pair, bool is true if subtree at this root can be drawn
// int is the max deg of any descendent of this root
// Still failing Testcase #5
pair<bool, int> dfs(int root) {
    vis[root] = 1;
    int cnt = 0;
    int maxdeg = 0;
    for (int next : graph[root]) if (!vis[next]) {
        pair<bool, int> p = dfs(next);
        if (!p.first) return make_pair(false, 0 /* do not care */);
        int deg = max((int)graph[next].size() - 1, p.second);
        if (deg > 2) cnt++;
        maxdeg = max(maxdeg, max(deg, (int)graph[next].size()));
    }
    return make_pair(cnt <= 2, maxdeg);
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    bool ans = dfs(0).first;
    cout << (ans ? "YES" : "NO") << endl;
}
