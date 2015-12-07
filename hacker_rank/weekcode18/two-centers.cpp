// two-centers.cpp
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int depth;
    int max1; int max1_id;
    int max2; int max2_id;
    int ext;
    int parent_id;
    vector<int> child;
};

int N;
int seen[5005];
int vis[5005];
int ignore[5005];
int dist[5005];
Node nodes[5005];

queue<int> que;
vector<vector<int>> graph;

void bfs(int s) {
    dist[s] = 0; que.push(s);
    while (!que.empty()) {
        int node = que.front(); que.pop();
        for (int next : graph[node]) if (!ignore[next] && dist[next] < 0) {
            dist[next] = dist[node] + 1;
            que.push(next);
        }
    }
}

void dfs(int s, int depth) {
    vis[s] = 1;
    nodes[s].depth = depth;
    for (int next : graph[s]) if (!ignore[next] && !vis[next]) {
        //cout << "dfs " << s << ' ' << next << endl;
        nodes[s].child.push_back(next);
        nodes[next].parent_id = s;
        dfs(next, depth + 1);
    }
}

void calc_tree(int s) {
    Node &curr = nodes[s];
    curr.max1 = 0;
    curr.max2 = 0;
    curr.max1_id = -1;
    curr.max2_id = -1;

    for (int c : curr.child) {
        calc_tree(c);
        int d  = nodes[c].max1 + 1;
        if (d > curr.max2) {
            curr.max2 = d;
            curr.max2_id = c;
        }
        if (curr.max2 > curr.max1) {
            swap(curr.max1, curr.max2);
            swap(curr.max1_id, curr.max2_id);
        }
    }
    //cout << s << ' ' << nodes[s].max1 << ' ' << nodes[s].max1_id << ' ' << nodes[s].max2 << ' ' << nodes[s].max2_id
    //    << ' ' << nodes[s].depth << endl;
}

void calc_ext(int s) {
    Node &curr = nodes[s];
    if (curr.parent_id >= 0) {
        int d1, d2;
        int p = curr.parent_id;
        if (nodes[p].max1_id == s) {
            d1 = nodes[p].max2;
        } else {
            d1 = nodes[p].max1;
        }
        d2 = nodes[p].ext;
        curr.ext = max(d1, d2) + 1;
    } else {
        curr.ext = 0;
    }
    for (int c : nodes[s].child) {
        calc_ext(c);
    }
    //cout << s << ' ' << curr.ext << endl;
}

bool check(int range, int start) {
    memset(seen, 0, sizeof seen);
    memset(ignore, 0, sizeof vis);
    memset(dist, -1, sizeof dist);
    memset(vis, 0, sizeof vis);

    bfs(start);
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

    // check unseen nodes
    int root = -1;
    for (int i = 0; i < N; ++i) if (!ignore[i]) {
        root = i;
        break;
    }
    nodes[root].parent_id = -1;
    dfs(root, 0);
    for (int i = 0; i < N; ++i) if (!seen[i] && !vis[i]) {
        return false;
    }

    calc_tree(root);
    calc_ext(root);
    int center2 = -1;
    int d2 = 5000;
    for (int i = 0; i < N; ++i) if (!ignore[i]) {
        int dnew = max(nodes[i].max1, nodes[i].ext);
        if (dnew < d2) {
            center2 = i;
            d2 = dnew;
        }
    }
    //cout << "d2 " << d2 << ' ' << "center " << center2 << endl;

    return d2 <= range;
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
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int lo = -1, hi = 5000;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi << endl;
}

