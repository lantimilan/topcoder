// game-on-tree.cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// player 1 starts at some node, then he can take all except largest subtree
// while player 2 gets the largest subtree

int N;
const int MAXN = 500000;
int weight[MAXN+5];
vector<int> graph[MAXN+5];
long long primary[MAXN+5];
long long total[MAXN+5];
int vis[MAXN+5];

long long dfs(int s) {
    vis[s] = 1;
    total[s] = weight[s];
    for (int next : graph[s]) if (!vis[next]) {
        long long child = dfs(next);
        total[s] += child;
        if (primary[s] < child) {
            primary[s] = child;
        }
    }
    return total[s];
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> weight[i];
    for (int i = 0; i < N-1; ++i) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1);
    long long all = total[1];
    long long opponent = all;
    for (int s = 1; s <= N; ++s) {
        long long curr = primary[s];
        long long parent = all - total[s];
        if (curr < parent) curr = parent;
        if (opponent > curr) opponent = curr;
    }
    long long ans = all - opponent;
    cout << ans << endl;
}
