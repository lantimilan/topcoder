// all pair shortest path
// Floyd-Warshall

#include <iostream>
#include <iomanip>
using namespace std;

int edge[105][105];
int dist[105][105];
int split[105][105];
int N, M;

void print(int s, int t)
{
    int k = split[s][t];
    if (k==-1) cout << s << ' ';
    print(s, k); cout << ' ';
    print(k, t);
}

int main()
{
    while (cin >> N && N != -1) {
        // all input edge is positive length
        for (int i=0; i<N; ++i)
        for (int j=0; j<N; ++j) {
            dist[i][j] = dist[j][i] = 0;
            edge[i][j] = edge[j][i] = 0;
            split[i][j] = split[j][i] = -1;
        }
        cin >> M;
        for (int i=0; i<M; ++i) {
            int a, b, len; cin >> a >> b >> len; --a, --b;
            if (edge[a][b] == 0 || edge[a][b] > len)
                edge[a][b] = edge[b][a] = len;
        }
        for (int i=0; i<N; ++i)
        {
        for (int j=0; j<N; ++j) cout << setw(4) << edge[i][j] << ' ';
        cout << endl;
        }

        for (int k=0; k<N; ++k)
        for (int i=0; i<N; ++i) if (i!=k)
        for (int j=i+1; j<N; ++j) if (j!=k)
        if (edge[i][k] > 0 && edge[k][j] > 0)
        {
            int cost = edge[i][k] + edge[k][j];
            if (dist[i][j] == 0 || dist[i][j] > cost) {
                dist[i][j] = dist[j][i] = cost;
                split[i][j] = split[j][i] = k;
            }
        }
        for (int k=0; k<N; ++k)
        for (int i=0; i<N; ++i) if (i!=k)
        for (int j=i+1; j<N; ++j) if (j!=k)
        {
            int update = -1;
            int cost;
            if (dist[i][k] > 0 && dist[k][j] > 0) {
                cost = dist[i][k] + dist[k][j];
                if (update == -1 || update > cost) { update = cost; }
            }
            if (dist[i][k] > 0 && edge[k][j] > 0) {
                cost = dist[i][k] + edge[k][j];
                if (update == -1 || update > cost) { update = cost; }
            }
            if (edge[i][k] > 0 && dist[k][j] > 0) {
                cost = edge[i][k] + edge[k][j];
                if (update == -1 || update > cost) { update = cost; }
            }
            if (update != -1) {
                dist[i][j] = dist[j][i] = update;
                split[i][j] = split[j][i] = k;
            }
        }
        int best = -1, s, t;
        for (int i=0; i<N; ++i)
        for (int j=i+1; j<N; ++j) if (dist[i][j] > 0 && edge[i][j] > 0)
        {
            int cost = dist[i][j] + edge[i][j];
            if (best < 0 || best > cost) {
                best = cost; s = i; t = j;
            }
        }
        cout << best << ' ' << s+1 << ' ' << t+1 << split[s][t]+1 << endl;
        if (best == -1) cout << best << endl;
        else {  // print route
            print(s, t);
            cout << endl;
        }
    }
}
