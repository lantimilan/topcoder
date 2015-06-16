// flight.cpp
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

int N, E, K;
vector<vector<pii>> graph;
vector<vector<pii>> extra;

const int INF = 1000 * 20000 * 10;
int dp[10000+5][1000+5];
int vis[10000+5];

void chmin(int &a, int b) {
    if (a > b) a = b;
}

void dfs1(int start, int k) {
    vis[start] = 1;
    for (pii p : graph[start]) {
        int node = p.first;
        int edge = p.second;
        if (!vis[node]) {  // update parent from child
            dfs1(node, k);
            chmin(dp[start][k], dp[node][k] + edge);
            //printf("dfs1: start %d child %d dist %d\n", start, node, dp[start][k]);
        }
    }
}

void dfs2(int start, int k) {
    vis[start] = 1;
    for (pii p : graph[start]) {
        int node = p.first;
        int edge = p.second;
        if (!vis[node]) {  // update child from parent
            chmin(dp[node][k], dp[start][k] + edge);
            //printf("dfs2: start %d child %d dist %d\n", start, node, dp[node][k]);
            dfs2(node, k);
        }
    }
}

int main() {
    cin >> N >> E >> K;
    graph.resize(N);
    for (int i = 0; i < N-1; ++i) {  // N-1 tree edges
        int a, b; cin >> a >> b; --a; --b;
        int w; cin >> w;
        graph[a].push_back(pii(b,w));
        graph[b].push_back(pii(a,w));
    }
    extra.resize(N);
    for (int i = 0; i < E; ++i) {  // shortcut edges
        int a, b; cin >> a >> b; --a; --b;
        int w; cin >> w;
        extra[a].push_back(pii(b,w));
        extra[b].push_back(pii(a,w));
    }

    for (int i = 0; i < N; ++i)
    for (int k = 0; k <= K; ++k) {
        dp[i][k] = INF;
    }

    // <= 1 to deal with a singleton graph
    for (int i = 0; i < N; ++i) if (graph[i].size() <= 1) {
        dp[i][0] = 0;
    }
    memset(vis, 0, sizeof vis); dfs1(0, 0);
    //for (int i = 0; i < N; ++i) { printf("%d: %d\n", i+1, dp[i][0]); }
    memset(vis, 0, sizeof vis); dfs2(0, 0);
    //for (int i = 0; i < N; ++i) { printf("%d: %d\n", i+1, dp[i][0]); }

    for (int k = 0; k < K; ++k) {
        for (int v = 0; v < N; ++v) dp[v][k+1] = dp[v][k];
        for (int v = 0; v < N; ++v) {
            for (pii p : extra[v]) {
                int node = p.first;
                int edge = p.second;
                chmin(dp[node][k+1], dp[v][k] + edge);
            }
        }
        memset(vis, 0, sizeof vis); dfs1(0, k+1);
        memset(vis, 0, sizeof vis); dfs2(0, k+1);
    }

    for (int v = 0; v < N; ++v) {
        printf("%d\n", dp[v][K]);
    }
}
