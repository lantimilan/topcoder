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

bool operator<(const pii &p1, const pii &p2)
{
    if (p1.first >=0 && p2.first < 0) return true;
    if (p1.first >=0 && p2.first >=0) return p1.first < p2.first;
    return false;
}

void dijkstra(int s)
{
    memset(dist, -1, sizeof dist);
    memset(vis, 0, sizeof vis);
    dist[s] = 0;
    priority_queue<pii> pq;
    pq.push(pii(dist[s], s));
    while(!pq.empty()) {
        int topdist = pq.top().first;
        int topnode = pq.top().second;
        pq.pop();
        if (vis[topnode]) continue;
        vis[topnode] = 1;
        for(int x=0; x<(int)edge[topnode].size(); ++x) {
            int next = edge[topnode][x].first;
            int dnew = topdist + edge[topnode][x].second;
            if (dist[next]<0 || dist[next] > dnew) {
                if (next == (int)edge.size()-1) {
                    dist[next] = dnew;
                }
                if (mp.find(pii(next,dnew)) == mp.end()) {
                    dist[next] = dnew;
                } else {
                    dist[next] = mp[pii(next, dnew)];
                }
                pq.push(pii(dist[next], next));
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
        int next;
        for(int j=0; j<s; j=next) {
            next=j+1;
            while(next < s && block[i][next] == block[i][next-1]+1)
                next++;
            int val = block[i][next-1]+1;
            for(int x=j; x<next; ++x) {
                avail[i][x] = val;
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
