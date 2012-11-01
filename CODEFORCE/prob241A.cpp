#include <cassert>
#include <cstdio>
#include <map>
#include <queue>
#include <set>
#include <utility>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int, pii> mykey_t;

int m, k;
int d[1005];
int s[1005];
int dist[1005];
map<pii, int> mp; // (pos, fuel) -> time
set<pii> vis;

class Comp {
public:
bool operator()(const pii &p1, const pii &p2) {
    assert(mp.find(p1) != mp.end());
    assert(mp.find(p2) != mp.end());
    return mp[p1] > mp[p2];
}
};

int dijkstra()
{
    priority_queue<pii, vector<pii>, Comp> pq;
    pq.push(pii(0, s[0])); // time, (pos, fuel)
    mp[pii(0, s[0])] = 0;

    while (!pq.empty()) {
        // get top
        pii kk = pq.top(); pq.pop();
        if (vis.find(kk) != vis.end()) continue;
        vis.insert(kk);
        int time = mp[kk];
        int pos = kk.first;
        int fuel = kk.second;

        if (pos == m) return time;

        for (int next = pos+1; next <= m; ++next) {
            int dd = dist[pos] - dist[next];
            int wait;
            if (fuel >= dd) wait = 0;
            else wait = (dd - fuel + s[pos]-1) / s[pos];

            for(int t = pos+1; t <= next; ++t) {
            int dd = dist[pos] - dist[t];
            int fnext = fuel + wait * s[pos] - dd;
            int tnext = time + dd + wait * k;
            if (fnext >= 0) {
                pii entry = pii(t, fnext+s[t]);
                if (mp.find(entry) == mp.end() || mp[entry] > tnext)
                    mp[entry] = tnext;
                pq.push(entry);
            }
            }
            //printf("pq time %d pos %d fuel %d\n",
            //    -pq.top().first,
            //    pq.top().second.first,
            //    pq.top().second.second);
        }
    }
}

int main()
{
    scanf("%d%d", &m, &k);
    for(int i=0; i<m; ++i) scanf("%d", d+i);
    for(int i=0; i<m; ++i) scanf("%d", s+i);

    dist[m] = 0;
    for(int i=m-1; i>=0; --i) {
        dist[i] = dist[i+1] + d[i];
    }
    int ans = dijkstra();
    printf("%d\n", ans);
}

// TLE
// MLE
// WA
