#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef long long int64;

const int MOD = (int)(1e9+7);

// trick,
// each round either x[i] move or y[i] move
// but consider x[i] + y[i] and x[i] - y[i]
// then both must move

int fact[60], invfact[60];;

class WolfPackDivTwo
{
public:

pair<int,int> extgcd(int a, int b)
{
	if (b == 1) return make_pair(0,1);
	pair<int,int> p = extgcd(b, a % b);
	int x, y;
	x = p.second;
	y = p.first - a/b * x;  // claim: int64 not needed
	//cout << "extgcd " << a << ' ' << x << ' ' << b << ' ' << y << endl;
	return make_pair(x, y);
}

int inv(int a)
{
	pair<int,int> p = extgcd(a, MOD); //cout << a << ' ' << p.first << ' ' << p.second << endl;
	int x = p.first;
	x = (x % MOD + MOD) % MOD;
	assert((int64)a * x % MOD == 1);
	return x;
}

void init()
{
	fact[0] = 1;
	for (int i = 1; i <= 50; ++i) fact[i] = (int64)fact[i-1] * i % MOD;
	for (int i = 0; i <= 50; ++i) {
		//cout << "i " << i << endl;
		invfact[i] = inv(fact[i]);
	}
}

int comb(int n, int r)
{
	//cout << n << ' ' << fact[n] << ' ' << r << ' ' << fact[r] << endl;
	return (int64)fact[n] * invfact[r] % MOD * invfact[n-r] % MOD;
}

int count_ways(vector<int> a, int m)
{
	int ans = 0;
	int minval, maxval;
	int n = a.size();
	minval = a[n-1] - m; maxval = a[0] + m;
	for (int x = minval; x <= maxval; ++x) { //cout << "val " << x << endl;
		int cur = 1;
		bool good = true;
		for (int i = 0; i < n; ++i) {
			int d = x + m - a[i];
			if (d % 2 != 0) { good = false; break; }
		}
		if (!good) continue;
		for (int i = 0; i < n; ++i) {
			int u = (m + x - a[i]) / 2;
			int v = m - u;
			//cout << u << ' ' << v << endl;
			cur = (int64)cur * comb(m, u) % MOD;
		}
		ans += cur;
		if (ans >= MOD) ans -= MOD;
		//cout << "ans " << ans << endl;
	}
	return ans;
}

int calc(vector <int> x, vector <int> y, int m)
{
	init();
	int n = x.size();
	vector<int> a(n), b(n);
	for (int i = 0;  i < n; ++i) {
		a[i] = x[i] + y[i];
		b[i] = x[i] - y[i];
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int c1, c2;
	c1 = count_ways(a, m);
	c2 = count_ways(b, m);
	return (int64)c1 * c2 % MOD;
}
};
