// special-pairs.cpp
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

// A biconnected component (bcc) is defined by an edge with parent being arti
// or root, and child being a non-arti. Edges within the same cycle is in the
// same bcc.
// To define a bcc, use a non-leaf, non-arti neighbor of an arti, then all
// vertices reachable, bounded by arti's, define this bcc. There is a catch,
// there might be no such node, because of pendant nodes, the leaf. Example is
// a triangle of 1,2,3, then 1-4, 2-5, 3-6. So we need to recursively remove
// all leaves.
// Why? A bridge is either both arti, or one arti and one leaf.
// Consider all non-leaf, non-arti nodes in such a subgraph, removing any one
// does not disconnect the subgraph, therefore any two nodes in this subgraph,
// including the bounding arti's, are connected by two edge-disjoint paths.
//
// bcc is defined by a collection of edges, but we work with vertices. For bcc,
// vertices are of three classes, arti, leaf (deg=1) and non-arti-non-leaf.
//
// if a node connects to a leaf, then it must be arti, because it is the only
// connection to the rest of graph.
//
// The standard way is to get all bridges, then build bcc starting with a non-
// bridge edge and collect all edges in the same bcc. This is because bcc
// form a partition of non-bridge edges.
//
// Definition: assume G is undirected and connected
//     articulation point v: the removal of v disconnects G
//     bridge e: the removal of e disconnects G
//     biconnected component bcc: e1 and e2 are in the same bcc iff they are in
// the same cycle.
int N, M, Q;
int CC;
int BCC;
vector<set<int>> graph;
vector<set<int>> label;
queue<int> que;

int is_root[100000+5];
int nchild[10000+5];
int low[100000+5];
int vis[100000+5];
int vis2[100000+5];
int discover[100000+5];
int parent[100000+5];
int arti[100000+5];

void chmin(int &x, int y) {
    if (x > y) x = y;
}

bool is_leaf(int v) {
    return graph[v].size() == 1;
}

void dfs2(int start) {
    vis2[start] = 1;
    for (int next : graph[start]) {
        label[next].insert(BCC);
        if (!arti[next] && !vis2[next]) {
            dfs2(next);
        }
    }
}

void dfs(int start) {
    vis[start] = 1;
    discover[start] = ++CC;
    low[start] = discover[start];
    for (int next : graph[start]) {
        if (!vis[next]) {
            parent[next] = start; nchild[start]++;
            dfs(next);
            chmin(low[start], low[next]);
            if (!is_root[start] && low[next] >= discover[start]) {
                arti[start] = 1;
            }
        } else if (next != parent[start]) { // grandparent or beyond
            chmin(low[start], discover[next]);
        }
    }
}

void process() {
    for (int i = 0; i < N; ++i) if (is_leaf(i)) {
        assert(graph[i].size() == 1);
        que.push(i);
        while (!que.empty()) {
            int start = que.front(); que.pop();
            int next = *graph[start].begin();
            graph[start].clear();
            graph[next].erase(start);
            if (is_leaf(next)) {
                que.push(next);
            }
        }
    }
}

void biconnected() {
    memset(is_root, 0, sizeof is_root);
    memset(nchild, 0, sizeof nchild);
    memset(vis, 0, sizeof vis);
    memset(vis2, 0, sizeof vis2);
    memset(parent, -1, sizeof parent);
    memset(arti, 0, sizeof arti);

    process();  // remove pendant vertices, recursively remove leaves
    CC = 0;
    for (int i = 0; i < N; ++i) if (!vis[i]) {
        is_root[i] = 1;
        dfs(i);
        if (nchild[i] > 1) {
            arti[i] = 1;
        }
    }

    for (int i = 0; i < N; ++i) if (!arti[i] && !is_leaf(i) && !vis2[i]) {
        BCC++;
        label[i].insert(BCC);
        dfs2(i);
    }
}

bool intersect(const set<int> &s1, const set<int> &s2) {
    if (s1.size() < s2.size()) {
        for (int e : s1) {
            if (s2.count(e)) return true;
        }
    } else {
        for (int e : s2) {
            if (s1.count(e)) return true;
        }
    }
    return false;
}

int main() {
    cin >> N >> M >> Q;
    graph.resize(N); label.resize(N);
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        graph[u].insert(v);
        graph[v].insert(u);
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

// WA and TLE, wrong algorithm
// Still WA ???? because I should just start from any non-arti-non-leaf to
// start a bcc.
// This one is wrong, yet it passed all test cases.
