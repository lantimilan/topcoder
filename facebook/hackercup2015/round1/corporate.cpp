// corporate.cpp
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MM = 200000;
int N;
vector<int> graph[MM+5];
int parent[MM+5];
int neighbor[MM+5];
int color[MM+5];
int nextcolor[MM+5];
long long delta[MM+5];
long long minsum[MM+5];
queue<int> que;

void solve(int tcase) {
    cin >> N;
    memset(parent, 0, sizeof parent);
    memset(neighbor, 0, sizeof neighbor);
    memset(color, 0, sizeof color);
    memset(nextcolor, 0, sizeof nextcolor);
    memset(delta, 0, sizeof delta);
    memset(minsum, 0, sizeof minsum);
    for (int i = 0; i <= N; ++i) graph[i].clear();

    for (int i = 0; i < N; ++i) {
        int p; cin >> p;
        int node = i+1;
        graph[p].push_back(node);
        parent[node] = p;
    }
    for (int i = 1; i <= N; ++i) {
        neighbor[i] = graph[i].size();
    }

    assert(que.empty());
    for (int i = 1; i <= N; ++i) if (neighbor[i] == 0) {
        minsum[i] = 1;
        delta[i] = 1;  // 2 - 1
        color[i] = 1;
        nextcolor[i] = 2;
        que.push(i);
    }
    while (!que.empty()) {
        int node = que.front(); que.pop();
        int p = parent[node]; if (p == 0) break;
        neighbor[p]--;
        if (neighbor[p] == 0) {
            // minsum, delta, color, nextcolor
            long long mintotal = 0;
            int nb = graph[p].size();
            vector<long long> extra(nb+3, 0);
            // nb child, one parent, max nb+2 possible colors to try
            for (int k = 1; k <= nb+2; ++k) {
                extra[k] = k;
            }
            for (int x = 0; x < nb; ++x) {
                int child = graph[p][x];
                mintotal += minsum[child];
                int kk = color[child];
                extra[kk] += delta[child];
            }
            int color1 = 0, color2 = 0;
            long long sum1, sum2;
            sum1 = sum2 = 1LL << 60;
            for (int k = 1; k <= nb+2; ++k) {
                long long value = extra[k];
                if (value < sum1) {
                    color2 = color1; sum2 = sum1;
                    color1 = k; sum1 = value;
                } else {
                    if (value < sum2) {
                        color2 = k; sum2 = value;
                    }
                }
            }
            assert(color1 > 0 && color2 > 0);
            minsum[p] = sum1 + mintotal;
            color[p] = color1;
            delta[p] = sum2 - sum1;
            nextcolor[p] = color2;
            que.push(p);
        }
    }
    long long ans = minsum[1];
    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}

