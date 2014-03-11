// GALACTIK.cpp

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int N, M;
vector< vector<int> > adj;
int cost[100000+5];
int reps[100000+5];
int vis[100000+5];
int COMP;

// return the node with mincost in component
int dfs(int s)
{
    vis[s] = 1;
    int ans = s;
    for (int i = 0; i < adj[s].size(); ++i) {
        int b = adj[s][i];
        if (!vis[b]) {
            int sub = dfs(b);
            if (cost[ans] < 0) ans = sub;
            else if (cost[sub] >= 0 && cost[sub] < cost[ans]) ans = sub;
        }
    }
    return ans;
}

int main()
{
    scanf("%d%d", &N, &M);
    adj.resize(N);

    for (int i = 0; i < M; ++i) {
        int v, w; scanf("%d%d", &v, &w);
        --v; --w;
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    for (int i = 0; i < N; ++i) scanf("%d", cost+i);

    // dfs to compute components
    // representative is mincost node in each component
    // if any compoenent has repcost < 0, ans is -1
    // else ans is sum of minnode * (k-1) + repcost of other components
    COMP = 0;
    memset(reps, -1, sizeof reps);
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < N; ++i) if (!vis[i]) {
        int r = dfs(i);
        reps[COMP++] = r;
    }

    if (COMP == 1) { printf("0\n"); return 0; }  // special case, connected

    int minnode = -1;
    for (int i = 0; i < N; ++i) if (cost[i] >= 0) {
        if (minnode < 0 || minnode > cost[i]) minnode = cost[i];
    }

    long long ans = -1;
    bool good = true;
    for (int i = 0; i < COMP; ++i) if (cost[reps[i]] < 0) {
        good = false; break;
    }
    if (good) {
        ans = 0;
        for (int i = 0; i < COMP; ++i) ans += cost[reps[i]];
        ans += 1LL * minnode * (COMP - 1 - 1);
    }
    printf("%lld\n", ans);
}

// Accepted
