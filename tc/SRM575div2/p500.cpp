#include <string>
#include <iostream>
using namespace std;

int dp[1005][2];


class TheNumberGameDivTwo
{
public:

bool isprime(int n)
{
	for (int k = 2; k * k <= n; ++k) if (n % k == 0) return false;
	return true;
}
int calc(int n, int turn)
{
//cout << "calc " << n << ' ' << turn << endl;
	if (dp[n][turn] >= 0) return dp[n][turn];
	if (n == 1 || isprime(n)) return dp[n][turn] = 0;  // lose
	for (int k = 2; k * k <= n; ++k) if (n % k == 0) {
		int d;
		d = k;
		if (calc(n - d, 1-turn) == 0) return dp[n][turn] = 1;		
		d = n / k;
		if (calc(n - d, 1-turn) == 0) return dp[n][turn] = 1;		
	}
	return dp[n][turn] = 0;
}

string find(int n)
{
	memset(dp, -1, sizeof dp);
	if (calc(n, 0)) return "John";
	else return "Brus";
}
};
