// for each K = 1 to M
// count number of ways to have sum = N with K elements
//
// it appears that the sequence is unordered, which makes counting rather difficult
// however we can impose an ordering, since each element has distinct S[i] % M
// we can count all sequences with mod M ordered increasingly, then the ans is obtained
// by multiplying by K factorial
//
// Now our job is to count number of sequence of K elements with mod M ordered increasingly
// if N is small, then we can use dp to count dp[sum][x][l] for number of sequences with 
// total = sum and use only mod M from 0 to x-1, with exactly l elements
// however N is huge, 10^18, so we need to work with N mod M somehow
//
// look at a valid sequence
// S[1] + S[2] + ... + S[K] = N
// this is true if and only if
// sum of (S[i] % M) = N % M + S / M  where S = sum of S[i]
// and 
// sum of (S[i] / M) = N / M - S / M
//
// if we write S[i] = Q[i] * M + R[i]
// then
// sum of R[i] = N % M + R / M  where R = sum of R[i]
// and
// sum of Q[i] = N / M - R / M
//
// if we have the R[i]'s, all we need is to find Q[i]'s to complete this equation
//
// Let dp[sum][x][l] be the number of ways to get total = sum, using mod M from 0 to x-1
// with exactly l elements,
// then for a given K, we look for adding up dp[sum][M][K] for which sum % M = N % M
// moreover, we need to multiply such dp[sum][M][K] by (Q + K-1 choose K-1) for Q = N/M - sum/M
// notice that K is at most 50 so the combination number can be computed efficiently

#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int MOD = (int)(1e9+7);
int dp[1300][55][55];
int fact[55], invfact[55];

class DistinctRemainders
{
public:

void refadd(int &a, int b)
{
	a += b;
	if (a >= MOD) a -= MOD;
}

int mult(int a, int b)
{
	return (long long)a * b % MOD;
}

int gcd(long long a, long long b)  // use long long even though only one of them can be long long
{
	if (b == 0) return a;
	return gcd(b, a % b);	
}

int choose(long long a, int b)  // compute (Q + K-1 choose K-1), K is at most 50, although Q can be 10^18
{
	int ans = 1;
	/*
	vector<int> v;
	for (int i=1; i<=b; ++i) v.push_back(i);
	for (int i = 0; i < b; ++i) {
		long long k = a - i;
		for (int j = 0; j < b; ++j) {
			int g = gcd(k, v[j]);
			if (g > 1) { k /= g; v[j] /= g; }  // careful, forgot to divide v[j] earlier
		}
		ans = (long long)ans * (k % MOD) % MOD;  // watch integer overflow, must reduce k by MOD
	}
	for (int j = 0; j < b; ++j) { if (v[j] > 1) cout << a << ' ' << b << endl;
	  assert(v[j] == 1);
	}
	*/
	for (int i = 0; i < b; ++i) ans = mult(ans, (a-i)%MOD);
	ans = mult(ans, invfact[b]);
	return ans;
}

int fastexp(int a, int b)
{
	int ans = 1;
	int base = a;
	while (b) {
		if (b&1) ans = mult(ans, base);
		base = mult(base, base);
		b /= 2;
	}
	return ans;
}

int inv(int a)
{
	return fastexp(a, MOD-2);
}

void init(int n)  // n is at most 50 in this problem
{
	fact[0] = 1;
	for (int i=1; i<=n; ++i)
		fact[i] = mult(fact[i-1], i);
	for (int i=0; i<=n; ++i)
		invfact[i] = inv(fact[i]);
}

int howMany(long long N, int M)
{
	if (M == 1) return 1;  // careful, M = 1 is special
	init(M);
	int ans = 0;
	for (int K = 1; K <= M; ++K) {
		//for (int sum = N%M; sum < M*M/2; sum += M)
		//for (int x = 0; x <= M; ++x)
		//for (int l = 0; l <= K; ++l)
			//dp[sum][x][l] = 0;
		dp[0][0][0] = 1;  // dp[sum][x][l] is number of increasing seq with total = sum using max <= x-1 with exactly l elements
		for (int sum = 0; sum < M*M/2; ++sum)
		for (int x = 0; x <= M; ++x)
		for (int l = 0; l <= K; ++l)
 		{
 			if (sum + x + l == 0) continue;
 			dp[sum][x][l] = 0;
 			if (x > 0) dp[sum][x][l] += dp[sum][x-1][l];
 			if (sum >= x-1 && x > 0 && l > 0) dp[sum][x][l] += dp[sum - (x-1)][x-1][l-1];
			if (dp[sum][x][l] >= MOD) dp[sum][x][l] -= MOD;
		}
		//cout << K << endl;
		
		int cur = 0;
		for (int sum = 0; sum < M*M/2 && sum <= N; ++sum)  // careful, sum can only be up to N
		if (sum % M == N % M) {
			//for (int x = 0; x <= M; ++x) {
				int tmp = dp[sum][M][K]; //cout << sum << ' ' << x << ' ' << K << ' ' << tmp << endl;
				long long Q = N / M - sum / M;
				assert(Q >= 0);  // careful, without check sum <= N, Q might be < 0 here
				tmp = mult(tmp, choose(Q + K-1, K-1));
				refadd(cur, tmp);
			//}
		}
		refadd(ans, mult(cur, fact[K]));
		
	}
	return ans;
}
};

// now it TLE, the dp I wrote is too slow, 50^6 is not acceptable in TC
// still fail, for N=14, M=7, ans is 643
// my return is 6403, how come? sum needs to be <= N
