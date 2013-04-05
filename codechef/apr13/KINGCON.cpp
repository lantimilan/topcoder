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

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int nedge[3005];
int adj[3005][3005];
int parent[3005];
int pre[3005];
int low[3005];
int vis[3005];
bool is_ap[3005];
int N, M, K;
int cnt;

void dfs(int s)
{
    vis[s] = 1;
    pre[s] = cnt++;
    low[s] = pre[s];
    for (int x = 0; x < nedge[s]; ++x) {
        int i = adj[s][x];
        if (!vis[i]) {  // tree edge
            parent[i] = s;
            dfs(i);
            low[s] = min(low[s], low[i]);
        } else {  // back edge
            if (parent[s] != i) low[s] = min(low[s], pre[i]);
        }
    }
    /*
    for (int x = 0; x < nedge[s]; ++x) {
        int i = adj[s][x];
        if (parent[s] != i) low[s] = min(low[s], pre[i]);
    }
    */
}

int count_ap(int root)
{
    cnt = 0;
    for (int i = 0; i < N; ++i) vis[i] = 0;
    parent[root] = -1;
    dfs(root);

    for (int i = 0; i < N; ++i) is_ap[i] = false;
    int ans = 0;
    int nchild = 0;
    // for non-root, it is AP iff there is a child has low[j] >= pre[i]
    for (int j = 0; j < N; ++j) {
        int i = parent[j];
        if (i == root) nchild++;
        if (low[j] >= pre[i] && i != root) is_ap[i] = true;
    }
    // for root, it is AP iff it has at least 2 children
    is_ap[root] = (nchild > 1);
    for (int i = 0; i < N; ++i) ans += (is_ap[i]);
    return ans;
}

int main()
{
    int T; scanf("%d", &T); //cin >> T;
    while (T--) {
        //cin >> N >> M >> K;
        scanf("%d%d%d", &N, &M, &K);
        for (int i = 0; i < N; ++i)
            nedge[i] = 0;

        for (int i = 0; i < M; ++i) {
            int a, b; //cin >> a >> b;
            scanf("%d%d", &a, &b);
            adj[a][nedge[a]++] = b;
            adj[b][nedge[b]++] = a;
        }
        int num_shield = count_ap(0);
        int cost = num_shield * K;
        //cout << cost << endl;
        printf("%d\n", cost);
    }
}

// Correct Answer
// Execution Time: 3.20
// must be cin/cout slow I/O, for N=3000 and M=N*(N-1)/2
// the input size is 80MB
// cin/cout runs in 0m2.386s
// scanf/printf runs in 0m0.792s
//
// TLE
// use adjlist to speed up dfs, still TLE
// OK, got TLE now
