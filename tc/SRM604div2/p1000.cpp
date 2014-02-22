#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int dp[55][55][55];  // root, numchild, target, # of subtrees rooted at root with its first numchild to reach target
vector<vector<int> > graph;
int edge[55][55];
int vis[55];
const int MOD = 1e9+7;

class FoxConnection2
{
public:

void dfs(int root, int N)
{
	for (int i = 0; i < N; ++i) if (edge[root][i] && !vis[i]) {
		graph[root].push_back(i);
		vis[i] = 1; dfs(i, N);
	}
}

void calc(int root, int N)
{
	for (int i = 0; i < graph[root].size(); ++i) calc(graph[root][i], N);
	
	dp[root][0][1] = 1;
	for (int i = 0; i < graph[root].size(); ++i) {
		int child = graph[root][i];
		int numchild = i+1;
		int childsize = graph[child].size();
		
		memcpy(dp[root][numchild], dp[root][numchild-1], sizeof dp[root][numchild]);
		for (int prev = 1; prev <= N; ++prev)
		for (int cur = 1; cur <= N-prev; ++cur)
		{
			int target = prev + cur;

			int &val = dp[root][numchild][target];
			val += (long long) dp[root][numchild-1][prev] * dp[child][childsize][cur] % MOD;
			if (val >= MOD) val -= MOD;
		}
	}
}

int ways(vector <int> A, vector <int> B, int k)
{
	int N = A.size() + 1;
	// init graph
	for (int i = 0; i < A.size(); ++i) {
		int a = A[i]-1;
		int b = B[i]-1;
		edge[a][b] = edge[b][a] = 1;
	}
	// construct tree
	graph.resize(N);
	vis[0] = 1;
	dfs(0, N);
	

	calc(0, N);
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		ans += dp[i][graph[i].size()][k];
		if (ans >= MOD) ans -= MOD;
	}
	return ans;
}

};
