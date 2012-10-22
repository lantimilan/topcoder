#include <iostream>
using namespace std;

typedef long long int64;
const int MOD = 1<<30;

int div[1000000+5];

int getdiv(int n)
{
		int ans=0;
		for(int k=1; k<=n/k; ++k) if (n%k == 0) {
			ans++;
			if (k != n/k) ans++;
		}
		return ans;
}


int main()
{
	int a, b, c; cin >> a >> b >> c;
	int64 sum=0;
	for(int i=1; i<=a; ++i)
	for(int j=1; j<=b; ++j)
	for(int k=1; k<=c; ++k)
	{
		int n = i*j*k;
		if (div[n]) {}
		else { div[n] = getdiv(n); }
		sum += div[n];
		if (sum > MOD) sum -= MOD;
	}
	cout << sum % MOD << endl;
}
