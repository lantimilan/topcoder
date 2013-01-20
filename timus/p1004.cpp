// for each pair (i, j)
// cut edge and do Dijkstra

#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

int edge[105][105];
int dist[105];
int done[105];
int pred[105];
int final[105];
int N, M;

void dijkstra(int s)
{
    for (int i=0; i<N; ++i) { dist[i] = -1; done[i] = 0; }
    dist[s] = 0; pred[s] = s;
    for (int x=0; x<N; ++x) {
        s = -1;
        for (int k=0; k<N; ++k) if (!done[k] && dist[k] >= 0)
            if (s==-1 || dist[k] < dist[s]) s = k;
        if (s < 0) return;
        done[s] = 1;
        for (int j=0; j<N; ++j) if (!done[j] && edge[s][j]) {
            int d = dist[s] + edge[s][j];
            if (dist[j] == -1 || dist[j] > d)  { dist[j] = d; pred[j] = s; }
        }
    }
}

int main()
{
    while (cin >> N && N != -1) {
        // all input edge is positive length
        for (int i=0; i<N; ++i)
        for (int j=0; j<N; ++j) {
            edge[i][j] = edge[j][i] = 0;
        }
        cin >> M;
        for (int i=0; i<M; ++i) {
            int a, b, len; cin >> a >> b >> len; --a, --b;
            if (edge[a][b] == 0 || edge[a][b] > len)
                edge[a][b] = edge[b][a] = len;
        }
        int best = -1, last;
        for (int s=0; s<N; ++s)
        for (int t=s+1; t<N; ++t) if (edge[s][t]) {
            int val = edge[s][t];
            edge[s][t] = edge[t][s] = 0;
            dijkstra(s);
            if (dist[t] >= 0) {
                int cost = dist[t] + val;
                if (best == -1 || best > cost) {
                    best = cost; last = t;
                    memcpy(final, pred, sizeof pred);
                }
            }
            edge[s][t] = edge[t][s] = val;
        }
        if (best == -1) cout << "No solution." << endl;
        else {
            while (last != final[last]) {
                cout << last+1 << ' ';
                last = final[last];
            }
            cout << last+1 << endl;
        }
    }
}

// 4729959  13:25:09 20 Jan 2013
// lantimilan  1004. Sightseeing Trip  C++ Accepted    0.734   264 KB
