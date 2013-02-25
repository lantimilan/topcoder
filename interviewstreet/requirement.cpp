// use edge to build graph
// find scc and DAG
// recurse from root to leaf

#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1007;

int pre[20], post[20], id[20];
int adj[20][20];
int path[20][20];
int vis[20];
int tick;
vector<int> order;
int n, m;

void dfs(int s)
{
    pre[s] = tick++;
    vis[s] = 1;
    for (int j=0; j<n; ++j) {
        if (!vis[j] && id[j] == j) dfs(j);
    }
    order.push_back(s);
    post[s] = tick++;
}

int calc(int low, int node)
{
    bool has_child = false;
    for (int i=0; i<n; ++i) if (adj[node][i] && id[i] == i)
        has_child = true;
    if (!has_child) return 10 - low;

    int ans = 0;
    for (int lo = low; lo < 10; ++lo)
    for (int i=0; i<n; ++i) if (adj[node][i] && id[i] == i) {
        ans += calc(lo, i);
        if (ans >= MOD) ans -= MOD;
    }
    return ans;
}

int main()
{
    cin >> n >> m;
    for (int i=0; i<m; ++i) {
        int a, b; cin >> a >> b;
        adj[a][b] = 1;
    }
    for (int i=0; i<n; ++i)
    for (int j=0; j<n; ++j) {
        path[i][j] = adj[i][j];
    }

    for (int k=0; k<n; ++k)
    for (int i=0; i<n; ++i) if (i != k)
    for (int j=0; j<n; ++j) if (j != k && i != j)
        path[i][j] |= path[i][k] & path[k][j];

    memset(id, -1, sizeof id);
    for (int i=0; i<n; ++i) if (id[i] < 0) {
        id[i] = i;
        for (int j=i+1; j<n; ++j) if (id[j] < 0) {
            if (path[i][j] && path[j][i]) id[j] = i;
        }
    }

    for (int i=0; i<n; ++i)
    for (int j=0; j<n; ++j) if (adj[i][j] && id[i] != id[j]) {
        adj[id[i]][id[j]] = 1;
    }

    memset(vis, 0, sizeof vis);
    for (int i=0; i<n; ++i) if (id[i] == i && !vis[i]) {
        dfs(i);
    }
    int ans = 1;
    int k = order.size();  // topo order
    for (int i=k-1; i>=0; --i) {
        int node = order[i];
        ans *= calc(0, node);
        ans %= MOD;
    }
    cout << ans << endl;
}
