// the graph is a tree, N-1 edges and connected
// from node 0, dispatch a boy to visit delivery point in dfs
// until time run out, then dispatch a second boy
// keep track of total cost

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 1000+5;
int N, M;
int boy, speed, gas;
double timelimit;
bool isdest[MAXN];
double time_mat[MAXN][MAXN];
int dist_mat[MAXN][MAXN];
int pred_mat[MAXN][MAXN];
int edge[MAXN][MAXN];
double rate[MAXN][MAXN];
int adj[MAXN][MAXN];
int cnt[MAXN];
int dist[MAXN];
int pred[MAXN];
double mytime[MAXN];

void dfs(int s)
{
	for(int i=0; i<cnt[s]; ++i) {
		int next = adj[s][i];
		if (dist[next] < 0) {
			dist[next] = dist[s] + edge[s][next];
			pred[next] = s;
			mytime[next] = mytime[s] + edge[s][next] / (rate[s][next] * speed);
			dfs(next);
		}
	}
}

void mytrace(int from, int to, vector<int> &path)
{
	int node = to;
	vector<int> curr;
	while(node != from) {
		curr.push_back(node);
		node = pred_mat[from][node];
	}
	for(int i=curr.size()-1; i>=0; --i)
		path.push_back(curr[i]);	
}

int main()
{
	scanf("%d%d", &N, &M);
	for(int i=0; i<M; ++i) {
		int dest; scanf("%d", &dest);
		isdest[dest] = true;
	}
	for(int i=0; i<N-1; ++i) {
		int x, y, d;
		double p;
		scanf("%d%d%d%lf", &x, &y, &d, &p);
		adj[x][cnt[x]++] = y;
		adj[y][cnt[y]++] = x;
		edge[x][y] = edge[y][x] = d;
		rate[x][y] = rate[y][x] = p;
	}
	scanf("%d%d%d%lf", &boy, &speed, &gas, &timelimit);
	timelimit /= 60;
	// do dfs for each node
	for(int s=0; s<N; ++s) {
		memset(dist, -1, sizeof dist);
		dist[s] = 0; mytime[s] = 0; pred[s] = s;
		dfs(s);
		for(int i=0; i<N; ++i) {
			dist_mat[s][i] = dist[i];
			time_mat[s][i] = mytime[i];
			pred_mat[s][i] = pred[i];
		}		
	}
	// dispatch boys
	int sites[MAXN];
	int KS=0;
	for(int i=0; i<N; ++i) if (isdest[i])
		sites[KS++] = i;

	//puts("dist");
	//for(int i=0; i<N; ++i) {
	//	for(int j=0; j<N; ++j)
	//		printf("%d ", dist_mat[i][j]);
	//	putchar('\n');
	//}
	//puts("time");
	//for(int i=0; i<N; ++i) {
	//	for(int j=0; j<N; ++j)
	//		printf("%.3lf ", time_mat[i][j]);
	//	putchar('\n');
	//}	

	int cost = 0;
	for(;;) {
		if (KS <= 0) break;
		// each iter uses a new boy
		cost += boy;
		vector<int> vec;
		double timeused = 0;
		int start = 0; vec.push_back(start);
		for( ; ; ) {
			if (KS <= 0) break;
			int idx = -1;
			for(int i=0; i<KS; ++i) {
				if (idx == -1 || dist_mat[start][sites[i]] < dist_mat[start][sites[idx]])
					idx = i;
			}			
			if (timeused + time_mat[start][sites[idx]] > timelimit ||
				gas * dist_mat[start][sites[idx]] > gas * dist_mat[0][sites[idx]] + boy)
				break;
			int next = sites[idx];
			timeused += time_mat[start][next];
			cost += gas * dist_mat[start][next];
			swap(sites[idx], sites[KS-1]); KS--;
			vec.push_back(next);
			start = next;
		}
		//printf("time used %.3lf\n", timeused);
		if (vec.size() > 1) {
			vector<int> path; path.push_back(0);
			for(int i=1; i<vec.size(); ++i) {
				mytrace(vec[i-1], vec[i], path);
			}
			printf("%d\n", path.size()-1);
			for(int i=0; i<path.size()-1; ++i) {
				printf("%d %d\n", path[i], path[i+1]);
			}
		}
	}
	//printf("total cost %d\n", cost);
}