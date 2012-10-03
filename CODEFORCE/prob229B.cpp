// dijkstra
// use int64
// inf as 1<<60
// if not reachable, -1

#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

int dist[100000+5];
int vis[100000+5];

vector<vector<pii> > edge;
vector<vector<int> > block;
vector<vector<int> > avail;
map<pii, int> mp;

// to use minheap you need to reverse operator less
class myless {
public:
    bool operator()(int p1, int p2)
    {
        if (dist[p1]<0 && dist[p2]>=0) return true;
        if (dist[p1]>=0 && dist[p2]>=0) return dist[p1]>dist[p2];
        return false;
    }
};

void dijkstra(int s)
{
    memset(dist, -1, sizeof dist);
    memset(vis, 0, sizeof vis);
    dist[s] = 0;
    while(mp.find(pii(s,dist[s])) != mp.end()) {
        dist[s]++;
    }
    priority_queue<int, vector<int>, myless> pq;
    pq.push(s);
    while(!pq.empty()) {
        int topnode = pq.top();
        int topdist = dist[topnode];
        pq.pop();
        if (topnode == (int)edge.size()-1) break;
        if (vis[topnode]) continue;
        vis[topnode] = 1;
        for(int x=0; x<(int)edge[topnode].size(); ++x) {
            int next = edge[topnode][x].first;
            int dnew = topdist + edge[topnode][x].second;

            int n = edge.size();
            if (next == n-1) {
                if (dist[next]<0) dist[next] = dnew;
                else if (dist[next] > dnew) dist[next] = dnew;
            } else {
                if (mp.find(pii(next,dnew)) == mp.end()) {
                    // do nothing
                } else {
                    dnew = mp[pii(next, dnew)];
                }
                if (dist[next]<0 || dist[next] > dnew) {
                    dist[next] = dnew;
                }
                pq.push(next);
            }
        }
    }
}

int main()
{
    int n, m; scanf("%d%d", &n, &m);
    edge.resize(n);
    for(int i=0; i<m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        --a; --b;
        edge[a].push_back(pii(b,c));
        edge[b].push_back(pii(a,c));
    }
    block.resize(n);
    for(int i=0; i<n; ++i) {
        int k; scanf("%d", &k);
        for(int j=0; j<k; ++j) {
            int t; scanf("%d", &t);
            block[i].push_back(t);
        }
    }
    avail = block;
    for(int i=0; i<n; ++i) {
        int s = block[i].size();
        for(int j=0; j<s; ) {
            int next=block[i][j];
            int x = j;
            for(++next, ++j; j<s && next == block[i][j]; ++j, ++next)
                ;
            for(; x<j; ++x) {
                avail[i][x] = next;
            }
        }
    }
    for(int i=0; i<n; ++i)
    for(int x=0; x<(int)block[i].size(); ++x)
        mp[pii(i,block[i][x])] = avail[i][x];
    // dijkstra
    dijkstra(0);
    printf("%d\n", dist[n-1]);
}
