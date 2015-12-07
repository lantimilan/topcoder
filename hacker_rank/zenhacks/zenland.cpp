// zenland.cpp
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int M = 1e5;
int P[M+5];
int Q[M+5];

int myleft[M+5];
int myright[M+5];
int deg[M+5];
int vis[M+5];
vector<int> graph[M+5];
int N;

void dfs(int s) {
    vis[s] = 1;
    for (int next : graph[s]) {
        if (!vis[next]) {
            if (myleft[s] < 0) { myleft[s] = next; dfs(next); }
            else {
                assert(myright[s] < 0);
                myright[s] = next; dfs(next);
            }
        }
    }
}

pair<long long, long long>  // (demand, cost)
calc(int root) {
    if (root < 0) {
        return make_pair(0, 0);
    }
    long long diff = Q[root] - P[root];
    pair<long long, long long> p1 = calc(myleft[root]);
    pair<long long, long long> p2 = calc(myright[root]);
    long long demand1 = p1.first;
    long long demand2 = p2.first;
    long long cost1 = p1.second;
    long long cost2 = p2.second;

    long long cost = cost1 + cost2 + abs(demand1) + abs(demand2);
    long long demand = diff + demand1 + demand2;

    //cout << root << ' ' << demand << ' ' << cost << endl;
    return make_pair(demand, cost);
}

int main() {
    memset(myleft, -1, sizeof myleft);
    memset(myright, -1, sizeof myright);

    cin >> N;
    for (int i = 0; i < N; ++i) cin >> P[i] >> Q[i];
    for (int i = 0; i < N-1; ++i) {
        int u, v; cin >> u >> v;
        deg[u]++; deg[v]++;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int root;
    for (int i = 0; i < N; ++i) if (deg[i] <= 2) {
        root = i; break;
    }
    assert(root < N);
    dfs(root);

    long long ans = calc(root).second;
    cout << ans << endl;
}
