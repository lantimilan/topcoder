#include <vector>
#include <string>

using namespace std;

vector<string> field;
int n, m;
int vis[60][60];
const int MOD = 1e9+7;

class GooseInZooDivTwo
{
public:

void dfs(int r, int c, int dist)
{
	vis[r][c] = 1;
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j) if (field[i][j] == 'v' && !vis[i][j]) {
		int d = abs(r-i) + abs(c-j);
		if (d <= dist) dfs(i,j,dist);
	}
}

int count(vector <string> _field, int dist)
{
	field = _field;
	n = field.size();
	m = field[0].size();
	
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
		vis[i][j] = 0;

	int comp = 0;
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
	if (field[i][j] == 'v' && !vis[i][j])
	{
		dfs(i, j, dist);
		comp++;
	}
	
	int ans = 1;
	for (int i = 0; i < comp; ++i) {
		ans = (long long)ans * 2 % MOD;
	}
	ans--;
	if (ans < 0) ans += MOD;
	return ans;
}

};
