#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <functional>
using namespace std;

// dijkstra's
// d[v] = min_(edge(u,v)) { max(d[u], w(u,v)) }

int vis[60][60];
int dist[60][60];

struct Node {
	int i, j;
	int d;
	Node() {}
	Node(int i1, int j1, int d1) { i=i1; j=j1; d=d1; }
};

class Cmp
{
public:
bool operator()(const Node &p1, const Node &p2)
{
	return p1.d > p2.d;
}
};

class ArcadeManao
{
public:


int shortestLadder(vector <string> level, int coinRow, int coinColumn)
{
	const int INF = 100;
	
	int n = level.size();
	int m = level[0].size();
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j) 
	{
		vis[i][j] = 0; dist[i][j] = INF;
	}
	
	//priority_queue< pair<int,int>, vector<pair<int,int> >, Cmp > que;
	priority_queue< Node, vector<Node>, Cmp > que;
	int i, j;
	i = n-1; j = 0;
	dist[i][j] = 0;
	que.push(Node(i,j,0));
	while (!que.empty()) {
		Node node = que.top(); que.pop();
		int i = node.i;
		int j = node.j;
		if (vis[i][j]) continue;
		//cout << i << ' ' << j << ' ' << dist[i][j] << endl;
		vis[i][j] = 1;
		
		// walk row
		int l, r;
		for (l = j; l >= 0 && level[i][l] == 'X'; --l) ;
		for (r = j; r < m && level[i][r] == 'X'; ++r) ;
		for (int k = l+1; k < r; ++k) {
			int update = dist[i][j];
			if (dist[i][k] > update) {
				dist[i][k] = update; que.push(Node(i,k,update));
			}
		}
		
		// walk col
		for (int r = 0; r < n; ++r) if (level[r][j] == 'X') {
			int update = max(dist[i][j], abs(i-r));
			if (dist[r][j] > update) {
				dist[r][j] = update; que.push(Node(r,j,update));
			}
		}
	}
	return dist[coinRow-1][coinColumn-1];
}
};
