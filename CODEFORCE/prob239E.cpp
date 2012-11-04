// split tree

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int adj[3005][3005];
int label[3005];
int vis[3005];
vector<pair<int,int> > edges;

int N;

void chmin(int &a, int b)
{
    a = a<b?a:b;
}

void dfs(int s, int mark)
{
    vis[s] = 1;
    label[s] = mark;
    for (int i=0; i<N; ++i) if (adj[s][i] || adj[i][s])
        if (!vis[i])
            dfs(i, mark);
}

// count #edge to reverse to visit all label == mark
int traverse(int s, int mark)
{
    int ans = 0;
    vis[s] = 1;
    for (int i=0; i<N; ++i) if (label[i] == mark)
    {
        if (adj[s][i] && !vis[i]) ans += traverse(i, mark);
        else if (adj[i][s] && !vis[i]) ans += traverse(i, mark) + 1;
    }
    return ans;
}

int solve(int a, int b)
{
    //printf("solve %d %d\n", a+1, b+1);
    memset(vis, 0, sizeof vis);
    int mark = 0;
    dfs(a, mark);
    mark = 1;
    dfs(b, mark);

    int cnt[2]; cnt[0] = cnt[1] = N;
    for (int k=0; k<N; ++k) {
        memset(vis, 0, sizeof vis);
        int rev = traverse(k, label[k]);
        //printf("k %d label %d rev %d\n", k+1, label[k], rev);
        chmin(cnt[label[k]], rev);
    }
    return cnt[0] + cnt[1];
}

int main()
{
    scanf("%d", &N);
    for (int i=0; i<N-1; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        --a, --b;
        adj[a][b] = 1;
        edges.push_back(make_pair(a, b));
    }
    int ans = N;
    for (int i=0; i<(int)edges.size(); ++i) {
        int a, b;
        a = edges[i].first; b = edges[i].second;
        adj[a][b] = 0;
        int curr = solve(a, b);
        ans = min(ans, curr);
        adj[a][b] = 1;
    }
    if (N==1) ans = 0;
    printf("%d\n", ans);
}

// TLE
// need dp
// for each node, remember left subtree result and right subtree result
