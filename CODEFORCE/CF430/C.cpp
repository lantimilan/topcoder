// C.cpp
//
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

const int MX = 1e5 + 5;
int odd[MX];
int even[MX];
int init[MX];
int goal[MX];
int vis[MX];

vector<vector<int> > graph;
vector<vector<int> > tree;
vector<int> nodes;

void dfs(int start)
{
    vis[start] = 1;
    for (int i = 0; i < graph[start].size(); ++i) {
        int next = graph[start][i];
        if (!vis[next]) {
            tree[start].push_back(next);
            dfs(next);
        }
    }
}

int process(int root)
{
    int cnt = even[root]; assert(cnt == 0 || cnt == 1);
    int flip = cnt;
    int cur = 0;
    int color = init[root];
    if (flip) color = 1 - color;
    if (color != goal[root]) { cur = 1; nodes.push_back(root); }

    even[root] ^= cur;
    int ans = cur;
    // for each child
    // update odd[child], even[child]
    // process child
    for (int x = 0; x < tree[root].size(); ++x) {
        int child = tree[root][x];
        odd[child] = even[root]; even[child] = odd[root];
        int childcnt = process(child);
        ans += childcnt;
    }
    return ans;
}

int main()
{
    int n; scanf("%d", &n);
    graph.resize(n);
    tree.resize(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(0);
    for (int i = 0; i < n; ++i) scanf("%d", &init[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &goal[i]);

    int ans = process(0);
    printf("%d\n", ans);
    for (int i = 0; i < nodes.size(); ++i) {
        printf("%d\n", nodes[i] + 1);
    }
}
