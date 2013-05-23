#include <vector>
#include <string>
#include <cstring>
#include <iostream>
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

	for (int j = 1; j < C; ++j) {
	//int colbest = 0;
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
    int sub = 0;
	for (int r = 0; r < R; ++r) {  // curr column, exclude occupied 'X'
		if (board[r][j] == 'X') { taken[1][r] = 1; sub |= 1<<r; }
	}

    if ((sub & b) != sub) continue;


	int curr = dp[j-1][p];
	for (int i = 0; i < R; ++i) if (b & 1<<i) if (!taken[1][i])
	{

		if (i+j & 1) {  // odd, white,
			// the two if below are not if/elseif, since even though
			// i-1 is a valid entry, it may not provide an L
			// so we fill in i-1 if possible, then we check i+1
			// to see if another L can be fit. If the two, i-1 and i+1
			// conflict, then taken[][] will take care of it

			if (i-1 >= 0) {  // try (i,j-1) and (i-1, j-1)
				if (!taken[0][i-1] && !taken[0][i]) {
					taken[0][i-1] = taken[0][i] = taken[1][i] = 1; curr++;
				}
			}
			if (i+1 < R) {  // try (i,j-1) and (i+1,j-1)
				if (!taken[0][i+1] && !taken[0][i]) {
					taken[0][i+1] = taken[0][i] = taken[1][i] = 1; curr++;
				}
			}

		} else {  // even, black,
			if (i-1 >= 0) {  // try (i-1,j) and (i,j-1)
                if (b & 1<<i-1)
				if (!taken[1][i-1] && !taken[0][i]) {
					taken[1][i-1] = taken[0][i] = taken[1][i] = 1; curr++;
				}
			}
			if (i+1 < R) {  // try (i,j-1) and (i+1,j)
                if (b & 1<<i+1)
				if (!taken[1][i+1] && !taken[0][i]) {
					taken[1][i+1] = taken[0][i] = taken[1][i] = 1; curr++;
				}
			}
		}
	}
	best = max(best, curr);
	}
	dp[j][b] = best;
	//colbest = max(colbest, best);
	}
	//cout << "col best " << j << ' ' << colbest << endl;
	}
	int ans = 0;
	for (int b = 0; b < (1<<R); ++b) ans = max(ans, dp[C-1][b]);
	return ans;
}
};


// Accepted
// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
