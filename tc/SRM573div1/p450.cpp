// claim: there is an opt path uses a[i] altitude only
// proof: given an opt path, convert into a path uses a[i] only
// first break the path into blocks with each block using a[k] < b[i] < a[k+1]
// then what happens inside block does not affect outside
// for each block, we can shift the whole thing towards + or -, until one node hits some a[i]
// then we effectively break the block into several blocks and we recurse
// in the end we have an optimal path with each node takes some a[i] altitude only, and in
// every step we never increase the path cost.
//
// then the problem becomes a shortest path problem with vertex (i, j) indicating node[i] is having altitude a[j]
//

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <cstring>
using namespace std;

const long long INF = 1LL << 60;

struct state {
	int pos, alt;
	long long dist;
};

bool operator<(state s1, state s2)
{
	return s1.dist > s2.dist;
}

priority_queue<state> pq;
int vis[55][55];

class SkiResorts
{
public:
long long minCost(vector <string> road, vector <int> altitude)
{
	memset(vis, 0, sizeof vis);
	int n = road.size();
	long long ans = INF;
	//for (int i=0; i<n; ++i) road[i][i] = 'Y';
	for (int j = 0; j < n; ++j) {
		int d = abs(altitude[j] - altitude[0]);
		state s = {0, j, d};
		pq.push(s);
	}
	while (!pq.empty()) {
		state cur = pq.top(); pq.pop();
		int pos = cur.pos;
		int alt = cur.alt;
		long long dist = cur.dist;
		//cout << pos << ' ' << alt << ' ' << dist << endl;
		if (vis[pos][alt]) continue;
		vis[pos][alt] = 1;		

		if (pos == n-1) { ans = dist; break; }
		
		for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) 
		if (road[pos][i] == 'Y' && altitude[alt] >= altitude[j])
		{
			if (!vis[i][j]) {
				long long d = dist + abs(altitude[i] - altitude[j]);
				state ss = {i, j, d};
				pq.push(ss);
			}
		}
	}
	if (ans >= INF) return -1;
	else return ans;
}
};
