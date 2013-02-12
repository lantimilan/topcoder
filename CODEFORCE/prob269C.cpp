// prob269C.cpp
//
// start at src=1
// sum[i] = sum of w(i,j) for all undirected (i,j) in E
// rem[i] flows not decided
//
// in each round identify a new src
// for each next of src
// rem[next] -= w(src, next)
// mark (src, next)
//
// new src is sum[i] - rem[i] == rem[i], outgoing only
// others has sum[i] - rem[i] < rem[i], incoming and outgoing
//
// use heap to keep track of sum[i] - 2*rem[i]

#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <cassert>
using namespace std;

typedef pair<int,int> pii;
vector<pii> edges;
vector<vector<pii> > adj;
priority_queue<pii> pq;
map<pii, int> orientation;
int sum[200000+5];
int rem[200000+5];
int vis[200000+5];

int main()
{
    int n, m; cin >> n >> m;
    adj.resize(n+1);
    for (int i=0; i<m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back(pii(b,c));
        adj[b].push_back(pii(a,c));
        sum[a] += c; sum[b] += c;
        edges.push_back(pii(a,b));
    }
    pq.push(pii(0,1));
    for (int i=2; i<=n; ++i) {
        rem[i] = sum[i];
        pq.push(pii(sum[i] - 2*rem[i], i));
    }
    while (!pq.empty()) {
        //cout << "pq " << pq.top().first << ' ' << pq.top().second << endl;
        if (pq.top().first != 0) break;
        int node = pq.top().second;
        pq.pop();
        assert(!vis[node]);
        vis[node] = 1;
        for (int x=0; x<adj[node].size(); ++x) {
            int next = adj[node][x].first;
            int flow = adj[node][x].second;
            if (vis[next]) continue;
            orientation[pii(node, next)] = 0;
            rem[next] -= flow; //cout << next << ' ' << rem[next] << endl;
            pq.push(pii(sum[next] - 2*rem[next], next));
        }
    }
    for (int i=0; i<m; ++i) {
        int a, b; a = edges[i].first; b = edges[i].second;
        if (orientation.count(pii(a,b))) cout << 0 << endl;
        else cout << 1 << endl;
    }
}
