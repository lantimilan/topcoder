#include <algorithm>
#include <cstring>
using namespace std;

// first, decide the state
// after throw n+1 .. 2N into A and B, we need to decide how to place 1..n
// state(n, A, B) is the number of ways to split 1..n after we put n+1..2N into A and B
// but the content of A and B can be huge
// now the observation: n can only be matched to n+1 to n+K if it was matched to a higher number
// but the number of subset is only 2^K and K is only 10
//
// so we can represent state as (n, 2^K), meaning the number of ways to put 1..n into A and B
// such that A contains n+p with p being the bits set in mask 2^K
// Now to move state (n, 2^K) to a previous state (n-1, 2^T) we can match n to one of the numbers 
// whose bit is set in masak 2^k
//
int dp[105][1<<10];
const int MOD = 1e9+7;

class AlienAndSetDiv2
{
public:

void update(int &a, int b)
{
	a += b;
	if (a >= MOD) a -= MOD;
}

int getNumber(int N, int K)
{
	dp[0][0] = 1;
	for (int n = 1; n <= 2*N; ++n)
	for (int mask = 0; mask < (1<<K); ++mask)
	{
		// mask is 0, then n can be in one of A and B
		if (mask == 0) {
			int prev = 1;
			update(dp[n][mask], dp[n-1][prev]);
			update(dp[n][mask], dp[n-1][prev]);
			continue;
		}
		// n is matched, then it must be matched to the top element in mask
		int mx = 0;
		for (int p = 0; p < K; ++p) if (mask & 1<<p) mx = p;		
		int prev = (mask & ~(1<<mx)) << 1;  // clear bit mx, and throw away n
		update(dp[n][mask], dp[n-1][prev]);

		if (mx != K-1) {  // n not matched, we can only do this when n is not matched to n+K
			int prev = mask << 1 | 1;
			update(dp[n][mask], dp[n-1][prev]);
		}
	}
	int ans = dp[2*N][0];
	return ans;
}

};
