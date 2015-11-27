// two-centers.cpp
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N;
int seen[5005];
int vis[5005];
int ignore[5005];
int deg[5005];
int dist[5005];
int dist2[5005];
queue<int> leaf;
queue<int> que;
vector<vector<int>> graph;

void bfs(int s, int d[]) {
    d[s] = 0; que.push(s);
    while (!que.empty()) {
        int node = que.front(); que.pop();
        for (int next : graph[node]) if (!ignore[next] && d[next] < 0) {
            d[next] = d[node] + 1;
            que.push(next);
        }
    }
}

bool check(int range, int start) {
    memset(seen, 0, sizeof seen);
    memset(ignore, 0, sizeof vis);
    memset(dist, -1, sizeof dist);

    bfs(start, dist);
    //cout << start << ' ' << range << endl;
    int cnt = 0;
    for (int i = 0; i < N; ++i) if (dist[i] <= range) {
        seen[i] = 1;
        ignore[i] = 1;
        cnt++;
    }
    if (cnt >= N) {
        return true;
    }

    // ignore subtree with all seen nodes.
//    assert(leaf.empty());
//    for (int i = 0; i < N; ++i) if (seen[i] && deg[i] <= 1) {
//        leaf.push(i); ignore[i] = 1;
//    }
//    while (!leaf.empty()) {
//        int node = leaf.front(); leaf.pop();
//        for (int next : graph[node]) if (seen[next] && !ignore[next]) {
//            deg[next]--;
//            if (deg[next] <= 1) {
//                leaf.push(next); ignore[next] = 1;
//            }
//        }
//    }

    // one center problem now, shrink subtree
    memset(deg, 0, sizeof deg);
    for (int i = 0; i < N; ++i) if (!ignore[i]) {
        for (int j : graph[i]) if (!ignore[j]) {
            deg[i]++;
        }
    }
    memset(vis, 0, sizeof vis);
    assert(leaf.empty());
    int center = -1;
    for (int i = 0; i < N; ++i) if (!ignore[i] && deg[i] <= 1) {
        leaf.push(i); vis[i] = 1;
    }
    while (!leaf.empty()) {
        int node = leaf.front(); leaf.pop();
        center = node;
        for (int next : graph[node]) if (!vis[next] && !ignore[next]) {
            if (--deg[next] <= 1) {
                leaf.push(next); vis[next] = 1;
            }
        }
    }
    assert(center >= 0 && !ignore[center]);
    //cout << "center " << center << endl;
    memset(dist2, -1, sizeof dist2);
    bfs(center, dist2);
    for (int i = 0; i < N; ++i) {
        int d = dist[i];
        if (dist2[i] >= 0) {
            if (d < 0 || d > dist2[i]) {
                d = dist2[i];
            }
        }
        assert(d >= 0);
        if (d > range) {
            return false;
        }
    }

    return true;
}

bool check(int range) {
    for (int s = 0; s < N; ++s) {
        if (check(range, s)) return true;
    }
    return false;
}

int main() {
    cin >> N;
    graph.resize(N);
    for (int i = 0; i < N-1; ++i) {
        int x, y; cin >> x >> y;
        --x; --y;
        graph[x].push_back(y); deg[x]++;
        graph[y].push_back(x); deg[y]++;
    }

    int lo = -1, hi = 5000;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi << endl;
}

