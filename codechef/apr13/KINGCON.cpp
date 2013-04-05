// KINGCON.cpp
//
// the problem asks for number of articulation points in an undirected graph
//
// algorithm: dfs
//
// start with any node as root
//
// low[i] = min(pre[i], low[j] for each child j of i)
//
// i is an articulation point if low[i] = pre[i] for non-root i
// for root, it is articulation point iff root has more than 1 branching

#include <cstring>
#include <iostream>
using namespace std;

int adj[3005][3005];
int parent[3005];
int pre[3005];
int low[3005];
int vis[3005];
int N, M, K;
int cnt;

void dfs(int s)
{
    vis[s] = 1;
    pre[s] = cnt++;
    low[s] = pre[s];
    for (int i = 0; i < N; ++i) if (!vis[i] && adj[s][i]) {  // tree edge
        parent[i] = s;
        dfs(i);
        low[s] = min(low[s], low[i]);
    }
    for (int i = 0; i < N; ++i) if (adj[s][i] && parent[s] != i) {  // back edge
        low[s] = min(low[s], pre[i]);
    }
}

int count_ap(int root)
{
    cnt = 0;
    for (int i = 0; i < N; ++i) vis[i] = 0;
    parent[root] = -1;
    dfs(root);

    /*
    for (int i = 0; i < N; ++i) {
        cout << i << ' ' << pre[i] << ' ' << low[i] << endl;
    }
    */

    int ans = 0;
    // for non-root, it is AP iff there is a child has low[j] >= pre[i]
    for (int i = 0; i < N; ++i) if (i != root) {
        bool is_ap = false;
        for (int j = 0; j < N; ++j) if (parent[j] == i) {
            if (low[j] >= pre[i]) is_ap = true;
        }
        ans += (is_ap);
    }
    // for root, it is AP iff it has at least 2 children
    int nchild = 0;  // stupid, use bool for nchild
    for (int j = 0; j < N; ++j) if (parent[j] == root) nchild++;
    ans += (nchild > 1);
    return ans;
}

int main()
{
    int T; cin >> T;
    while (T--) {
        for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            adj[i][j] = 0;

        cin >> N >> M >> K;
        for (int i = 0; i < M; ++i) {
            int a, b; cin >> a >> b;
            adj[a][b] = adj[b][a] = 1;
        }
        int num_shield = count_ap(0);
        int cost = num_shield * K;
        cout << cost << endl;
    }
}

// OK, got TLE now
