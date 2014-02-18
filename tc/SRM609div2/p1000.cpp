#include <cstring>
using namespace std;

int dp[55][55][55][55];

class VocaloidsAndSongs
{
public:

int count(int S, int gumi, int ia, int mayu)
{
	dp[0][0][0][0] = 1;
	for (int song = 1; song <= S; ++song) {
		for (int g1 = 0; g1 <= gumi; ++g1)
		for (int i1 = 0; i1 <= ia; ++i1)
		for (int m1 = 0; m1 <= mayu; ++m1)
		if (dp[song-1][g1][i1][m1] >= 0)
		for (int g = 0; g <= 1; ++g)
		for (int i = 0; i <= 1; ++i)
		for (int m = 0; m <= 1; ++m)
		if (g + i + m > 0)
		{
			const int MOD = 1e9+7;
			int g2 = g1 + g;
			int i2 = i1 + i;
			int m2 = m1 + m;
			if (g2 <= gumi && i2 <= ia && m2 <= mayu)
			{
				int &ref = dp[song][g2][i2][m2];
				if (ref < 0) ref = dp[song-1][g1][i1][m1];
				else ref += dp[song-1][g1][i1][m1];
				if (ref >= MOD) ref -= MOD;
			}
		}
	}
	return dp[S][gumi][ia][mayu];
}
};
