#include <vector>
using namespace std;

int adj[55][55];
int vis[55];
long long dp[55];  // number of subtree rooted at node i
int N;

class CentaurCompanyDiv2
{
public:

long long calc(int root)
{
	vis[root] = 1;
	if (dp[root] > 0) return dp[root];
	long long ans = 1;
	for (int ch = 0; ch < N; ++ch) if (adj[root][ch] && !vis[ch]) {
		ans *= (calc(ch)+1);
	}
	return dp[root] = ans;
}

long long count(vector <int> a, vector <int> b)
{
	N = a.size()+1;
	for (int i = 0; i < a.size(); ++i) {
		int x, y;
		x = a[i]-1; y = b[i]-1;
		adj[x][y] = adj[y][x] = 1;
	}
	calc(0);
	long long ans = 0;
	for (int i = 0; i < N; ++i)
		ans += dp[i];
	return ans+1;
}

};
