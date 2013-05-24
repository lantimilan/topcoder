// 1. first idea is to use vector<pair<prime, cnt> >, but this is too much memory
// instead, get cnt for each prime by computing n!k
//
// 2. cnt could be much more than 1e9+9, so reduce to MOD every time possible
// use long long may be very slow and likely to integer overflow
//
#include <vector>
#include <iostream>
#include <utility>
using namespace std;

int dp[1001][101];
int primes[200];
int isprime[1005];
int P;

const int MOD = 1e9+9;
// do count for each prime
class MegaFactorialDiv2
{
public:

void init()
{
	for (int i = 0; i <= 1000; ++i) isprime[i] = 1;
	for (int i = 2; i <= 1000; ++i) if (isprime[i]) {
		primes[P++] = i;
		for (int j = i*i; j <= 1000; j+=i) isprime[j] = 0;
	}
	cout << "primes " << P << endl;
}

int calc(int n, int k, int p)
{
	if (dp[n][k] >= 0) return dp[n][k];
	if (n == 0) return 0;
	if (k == 0) {
		int &ans = dp[n][k]; ans = 0;
		while (n % p == 0) { n /= p; ans++; if (ans >= MOD) ans -= MOD; }
		return ans;
	}
	int v1 = calc(n, k-1, p);
	int v2 = calc(n-1, k, p);
	int &ans = dp[n][k];
	ans = v1 + v2;
	if (ans >= MOD) ans -= MOD;
	return ans;
}

int countDivisors(int N, int K)
{
	init();

	int ans = 1;
	for (int x = 0; x < P; ++x) {
		//cout << x << endl;
		memset(dp, -1, sizeof dp);
		int c = calc(N, K, primes[x]);
		ans = (long long )ans * (1 + c) % MOD;
	}
	return ans;
}
};
