// Did I read the problem correctly?
//

#include <vector>
#include <string>
#include <cstring>
using namespace std;

int dp[50][1<<4];

class TheTilesDivTwo
{
public:
int find(vector <string> board)
{
	int R = board.size(), C = board[0].size();
	memset(dp, -1, sizeof dp);

	int mask = 0;
	for (int i = 0; i < R; ++i) if (board[i][0] == 'X') mask |= 1<<i;
	dp[0][mask] = 0;

	for (int j = 1; j < C; ++j)
	for (int b = 0; b < (1<<R); ++b)
	{
	int best = -1;
	for (int p = 0; p < (1<<R); ++p) if (dp[j-1][p] >= 0)
	{

	int taken[2][4]; memset(taken, 0, sizeof taken);
	// cells that cannot be used
	for (int r = 0; r < R; ++r) {  // prev column, exclude entries already in use
		if (p & 1<<r) taken[0][r] = 1;
	}
	for (int r = 0; r < R; ++r) {  // curr column, exclude occupied 'X'
		if (board[r][j] == 'X') taken[1][r] = 1;
	}

	int curr = dp[j-1][p];
	for (int i = 0; i < R; ++i) if (b & 1<<i) if (!taken[1][i])
	{
		if (i+j & 1) {  // odd, white,
			if (i-1 >= 0) {  // try (i,j-1) and (i-1, j-1)
				if (!taken[0][i-1] && !taken[0][i]) {
					taken[0][i-1] = taken[0][i] = taken[1][i] = 1; curr++;
				}
			} else if (i+1 < R) {  // try (i,j-1) and (i+1,j-1)
				if (!taken[0][i+1] && !taken[0][i]) {
					taken[0][i+1] = taken[0][i] = taken[1][i] = 1; curr++;
				}
			}

		} else {  // even, black,
			if (i-1 >= 0) {  // try (i-1,j) and (i,j-1)
				if (!taken[1][i-1] && !taken[0][i]) {
					taken[1][i-1] = taken[0][i] = taken[1][i] = 1; curr++;
				}
			} else if (i+1 < R) {  // try (i,j-1) and (i+1,j)
				if (!taken[1][i+1] && !taken[0][i]) {
					taken[1][i+1] = taken[0][i] = taken[1][i] = 1; curr++;
				}
			}
		}
	}
	// submask must agree with b
	int sub = 0;
	for (int r = 0; r < R; ++r) if (taken[1][r]) sub |= 1<<r;
	if ((sub & b) != sub) continue;
	best = max(best, curr);
	}
	dp[j][b] = best;
	}
	int ans = 0;
	for (int b = 0; b < (1<<R); ++b) ans = max(ans, dp[C-1][b]);
	return ans;
}
};

