#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

const int MOD = 1e9+7;
int vis[55][55];

class GooseInZooDivOne {
public:

int calc(int i1, int j1, int i2, int j2)
{
	return abs(i1 - i2) + abs(j1 - j2);
}

int dfs(int r, int c, int n, int m, int dist, const vector<string> &field)
{
	int ans = 1;
	vis[r][c] = 1;
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j) if (!vis[i][j] && field[i][j] == 'v' && calc(i,j,r,c) <= dist)
	{
		ans += dfs(i,j,n,m,dist,field);
	}
	return ans;
}

int count(vector <string> field, int dist)
{
	vector<int> s;

	memset(vis, 0, sizeof vis);
	int n = field.size();
	int m = field[0].size();
	int a = 0, b = 0;
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j) if (!vis[i][j] && field[i][j] == 'v') {
		int cnt = dfs(i,j,n,m,dist,field);
		s.push_back(cnt);
		if (cnt & 1) a++;
		else b++;
	}
	int ans = 1;
	for (int i = 0; i < b; ++i) {
		ans = (long long)ans * 2 % MOD;
	}
	for (int i = 0; i < a-1; ++i) {
		ans = (long long)ans * 2 % MOD;
	}
	return ans -1;
}

};


// contest version
