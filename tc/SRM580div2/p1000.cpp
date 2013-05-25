#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

// the optimal strategy for Eel is to force a large cost up to R-2
// then the next move for Rabbit must be go down one column
const int INF = 1e9;
int dp[60][60];
class WallGameDiv2
{
public:
int play(vector <string> costs)
{
	int R = costs.size(), C = costs[0].size();
	dp[0][0] = 0;
	int j;
	for (j = 1; j < C; ++j) {
		if (costs[0][j] == 'x') break;
		else dp[0][j] = dp[0][j-1] + costs[0][j] - '0';
	}
	for (; j < C; ++j) dp[0][j] = INF;
	
	for (int i = 1; i < R-1; ++i)
	for (int j = 0; j < C; ++j) {
	dp[i][j] = INF;
	for (int k = 0; k < C; ++k) if (dp[i-1][k] < INF)
	{
		bool wall = false;
		for (int t = min(j,k); t <= max(j,k); ++t) if (costs[i][t] == 'x') wall = true;
		if (wall) continue;
		int curr = dp[i-1][k];
		for (int t = min(j,k); t <= max(j,k); ++t) curr += costs[i][t] - '0';
		if (dp[i][j] == INF || dp[i][j] < curr) dp[i][j] = curr;
	}
	}
	int ans = 0;
	for (int j = 0; j < C; ++j) if (dp[R-2][j] < INF && costs[R-1][j] != 'x') {
		int curr = dp[R-2][j] + costs[R-1][j] - '0';
		ans = max(ans, curr); 
	}
	return ans;
}
};
