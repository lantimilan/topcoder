// special-pairs.cpp
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int N, M, Q;

vector<vector<int>> graph;
vector<set<int>> label;

int low[100000+5];
int vis[100000+5];
int done[100000+5];
int depth[100000+5];
int size[100000+5];
int parent[100000+5];
int arti[100000+5];

void chmin(int &x, int y) {
    if (x > y) x = y;
}

void dfs2(int start, int subtree) {
    label[start].insert(subtree); size[subtree]++;
    for (int next : graph[start]) if (parent[next] == start && !done[next]) {
        dfs2(next, subtree);
    }
    done[start] = 1;
}

void dfs(int start, int dep) {
    vis[start] = 1;
    depth[start] = dep;
    low[start] = dep;
    for (int next : graph[start]) {
        if (!vis[next]) {
            parent[next] = start;
            dfs(next, dep+1);
            chmin(low[start], low[next]);
            if (low[next] >= dep) {
                arti[start] = 1;
            }
        } else if (next != parent[start]) {
            chmin(low[start], depth[next]);
        }
    }
    for (int next : graph[start]) if (parent[next] == start) {
        if (low[next] >= dep) {
            dfs2(next, next);
            label[start].insert(next); size[next]++;
        }
    }
}

void biconnected() {
    memset(vis, 0, sizeof vis);
    memset(done, 0, sizeof done);
    memset(parent, -1, sizeof parent);
    memset(arti, 0, sizeof arti);
    dfs(0, 1);

/*
    for (int i = 0; i < N; ++i) {
        cout << (i+1) << ' ' << depth[i] << endl;
    }
    for (int i = 0; i < N; ++i) if (arti[i]) {
        cout << (i+1) << ' ';
    } cout << endl;

    for (int i = 0; i < N; ++i) {
        cout << (i+1) << ": ";
        for (int l : label[i]) {
            cout << l+1 << ' ';
        } cout << endl;
    }
    */
}

bool intersect(const set<int> &s1, const set<int> &s2) {
    if (s1.size() < s2.size()) {
        for (int e : s1) {
            if (s2.count(e) && size[e] > 2) return true;
        }
    } else {
        for (int e : s2) {
            if (s1.count(e) && size[e] > 2) return true;
        }
    }
    return false;
}

int main() {
    cin >> N >> M >> Q;
    graph.resize(N); label.resize(N);
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u  >> v; --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    biconnected();

    for (int i = 0; i < Q; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        if (intersect(label[u], label[v])) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
