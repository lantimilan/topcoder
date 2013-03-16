// this is a math problem
//
// 1. if we consider x[i] + y[i] for i = 0 to n-1,
// then the only way for i and j to meet is to 
// have x[i] + y[i] with the same parity as x[j] + y[j]
// because in every step, both change their parity
// so first check if all x[i] + y[i] must have same parity
// and ans is 0 if not
//
// 2. now we count the number of ways the wolves can meet
// first notice that the x and y are independent, we can
// count the number of ways x values meet and y values meet
// then just multiply them
// consider the minval and maxval of x, call it v
// then minval = v[n-1] - M and maxval = v[0] + M
// assuming v[0] .. v[n-1] are sorted
//
// there is a catch here, some wolf might have both odd parity for
// x and y, while some might have both even parity for x and y
//
// solution by wcao: since x[i] + y[i] and x[i] - y[i] uniquely determine
// x[i] and y[i], we can work on these two quantities instead, then both
// have same parity as M
//
// now we count for each val from minval to maxval
// for a given v[i], how many ways it can make to val
// let there be a count of a +1 and a count of b -1
// then a + b = M for M rounds
// a - b = val
// so the number of ways is (M choose a) which is (M choose (M+val)/2)
// notice that val must have the same parity with M to have nonzero result
//
// although I looked at wcao's solution, when implement it myself,
// integer overflow everywhere

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int MOD = (int)(1e9+7);

int fact[100000+5];
int invfact[100000+5];

class WolfPack
{
public:


int fastpow(int a, int b)
{
	int ans = 1;
	int base = a;
	while (b) {
		if (b&1) ans = (int64)ans * base % MOD;
		base = (int64)base * base % MOD;
		b /= 2;
	}
	return ans;
}

int inv(int a)
{
	return fastpow(a, MOD-2);
}

int comb(int n, int k)
{
	int deno = (int64)invfact[k] * invfact[n-k] % MOD; //cout << "deno " << deno << ' ' << inv(deno) << ' ' << fact[k] << ' ' << fact[n-k] << endl;
	int ans = (int64)fact[n] * deno % MOD;
	//cout << "comb " << n << ' ' << k << ' ' << ans << endl;
	return ans;
}

void init()
{
	fact[0] = 1;
	for (int i=1; i<100005; ++i) fact[i] = (int64)fact[i-1] * i % MOD;
	//for (int i=0; i < 10; ++i) cout << fact[i] << endl;
	for (int i=0; i<100005; ++i) invfact[i] = inv(fact[i]);
}


int calc(vector <int> v, int m)
{
	sort(v.begin(), v.end());
	int minval, maxval;
	int n = v.size();
	int64 ans = 0;
	for (int i = 1; i < n; ++i) if ((v[i] & 1) != (v[0] & 1)) { return 0; }
	minval = v[n-1] - m;
	maxval = v[0] + m;
	for (int val = minval; val <= maxval; val += 2)  // val and m must be same parity
	{
		int tmp = 1;
		for (int i = 0; i < n; ++i) {
			int diff = abs(val - v[i]);
			tmp = (int64)tmp * comb(m, (m - diff)/2) % MOD; //cout << tmp << ' ' << val << ' ' << i << ' ' << v[i] << ' ' << diff << endl;
		}
		//ans = ((int64)ans + tmp) % MOD;
		ans += tmp;
		if (ans >= MOD) ans -= MOD;
	}
	return ans;
}

int calc(vector <int> x, vector <int> y, int m)
{
	int n = x.size();
	init();
	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i) {
		a[i] = x[i] + y[i];
		b[i] = x[i] - y[i];
	}
	return (int64)calc(a, m) * calc(b, m) % MOD;
}
};
