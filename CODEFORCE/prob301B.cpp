// prob301B.cpp

// binary search and dfs

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int a[105];
int x[105];
int y[105];
int vis[105];

int n;
int d;

bool check(int budget)
{
    priority_queue<pair<int, int> > pq;
    pq.push(make_pair(budget, 1));

    memset(vis, 0, sizeof vis);
    while (!pq.empty()) {
        int node = pq.top().second;
        int money = pq.top().first;
        pq.pop();
        if (vis[node]) continue;
        vis[node] = 1;
        money += a[node];
        for (int i = 1; i <= n; ++i) if (!vis[i]) {
            int cost = abs(x[node] - x[i]) + abs(y[node] - y[i]);
            cost *= d;
            if (money >= cost) pq.push(make_pair(money - cost, i));
        }
    }
    return vis[n];
}

int main()
{
    cin >> n >> d;
    for (int i = 1; i <= n; ++i) a[i] = 0;
    for (int i = 2; i < n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i];

    int lo = 0, hi = 400 * d;
    while (lo + 1 < hi) {
        int m = (lo + hi) / 2;
        if (check(m)) hi = m;
        else lo = m;
    }
    cout << hi << endl;
}

// Accepted
