// Observation:
// 1. operations can be performed in any order
// 2. a cycle of 10 operations is equivalent to none (not useful for this problem)
// 3. if two operations are of opposite directions, then they do not overlap (proof: we can cancel out those operations in overlapped segment)
//
// state: (pos, move) is the minimum number of operations to get prefix[0..pos] from S[] to T[] with pos operated with move
// transition:
// move can be -500 to 500, where 500 = 50 * 10
// for each pos from 0 to n-1
// for each move from 0 to 1000 (offset=500)
// for each prev from 0 to 1000
// we go from (pos-1, prev) to (pos, move)
// if prev and move are opposite, then cost for pos is move
// else cost for pos is 0 if prev > move, or move - prev otherwise

#include <string>
#include <cstring>
#include <cassert>
using namespace std;

const int OFFSET = 500;
int dp[60][1005];

class CombinationLockDiv2
{
public:

void update(int &target, int val)
{
	if (val >= 0) {
		if (target < 0 || target > val) target = val;
	}
}

int minimumMoves(string S, string T)
{
	memset(dp, -1, sizeof dp);
	dp[0][OFFSET] = 0;
	int n = S.length();
	for (int pos = 1; pos <= n; ++pos) {
		for (int move = 0; move <= 1000; ++move)
		for (int prev = 0; prev <= 1000; ++prev)
		if (dp[pos-1][prev] >= 0) {
			int shift = move - OFFSET;
			int shiftX = prev - OFFSET;
			int src = S[pos-1] - '0';
			int dest = T[pos-1] - '0';
			int target = (src + shift) % 10; if (target < 0) target += 10;
			if (target == dest) {
				int cost;
				int ABSshift = abs(shift);
				int ABSshiftX = abs(shiftX);
				if (shiftX * shift >= 0) {  // watch integer overflow
					if (ABSshiftX >= ABSshift) cost = 0;
					else cost = ABSshift - ABSshiftX;
				} else {
					cost = ABSshift;
				}
				update(dp[pos][move], dp[pos-1][prev] + cost);
			}
		}
	}
	int ans = -1;
	for (int move = 0; move <= 1000; ++move) {
		update(ans, dp[n][move]);
	}
	assert(ans >= 0);
	return ans;
}
};
