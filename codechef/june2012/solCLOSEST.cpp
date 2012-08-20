/**
 * June 2012 Codechef Long Contest
 *
 * Problem:  CLOSEST
 * Author:   Anton Lunyov (Tester)
 * Score:    10284.9375 out of 50000
 * Timing:   3.89 out of 4.00
 *
 * Short Description:
 * When we create neat test data for this problem we were faced with the issue
 * that for many tests the total number of different answers is rather low.
 * It allows to get almost perfect score for such tests. Namely, we can
 * calculate answers for several random banks by naive solution and save all
 * these answers. And then for each remaining bank try only these saved response
 * centers. Here we present this solution just for fun :)
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

ULL sqr(int x) {
	return LL(x) * x;
}

// Square of distance between points under the given constraints can be up to
// 12 * 10^18 and doesn't fit in "long long" but fits in "unsigned long long"
// hence we calculate it in ULL. Tests were carefully designed to fail solutions
// that do this with long long or with double. However double at gnu C++ is 
// magic and somehow can find at least one correct answer always.
// In this special test that should fail solutions with double for each bank
// there is only one closest response center with distance say D near 5e18
// and all response centers having distance < D + 15000 and near 100 response
// centers have distance < D + 100. So double MUST FAIL to find the closest
// point in this situation since all these distances are indistinguishable by
// double - its accuracy is only 14-15 digits, but distances are differ in
// 17-18th digit (at least for 100 points).
// I am really sad and angry that solutions with double passed :(
ULL norm2(int x, int y, int z) {
	return sqr(x) + sqr(y) + sqr(z);
}

const int maxN = 50000;
const int maxQ = 50000;
int X[maxN], Y[maxN], Z[maxN]; // response centers
int A[maxQ], B[maxQ], C[maxQ]; // banks
int res[maxQ];
int candidates[maxN];

int main()
{
	clock_t start = clock();

	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d %d", X + i, Y + i, Z + i);
	}

	int Q;
	scanf("%d", &Q);
	for (int q = 0; q < Q; ++q) {
		scanf("%d %d %d", A + q, B + q, C + q);
		res[q] = -1;
	}

	int len = 0;
	for (int q = 0; q < Q; ++q) {
		if (rand() % 75) {
			continue;
		}
		ULL best = 13e18;
		for (int i = 0; i < N; ++i) {
			ULL cur = norm2(X[i] - A[q], Y[i] - B[q], Z[i] - C[q]);
			if (best > cur) {
				res[q] = i;
				best = cur;
			}
		}
		candidates[len++] = res[q];
	}
	sort(candidates, candidates + len);
	len = unique(candidates, candidates + len) - candidates;
	random_shuffle(candidates, candidates + len);

	for (int q = 0; q < Q; ++q) {
		if (res[q] == -1) {
			ULL best = 13e18;
			for (int j = 0; j < len && j < 200; ++j) {
				int i = candidates[j];
				ULL cur = norm2(X[i] - A[q], Y[i] - B[q], Z[i] - C[q]);
				if (best > cur)
				{
					res[q] = i;
					best = cur;
				}
			}
		}
		printf("%d\n", res[q]);
	}
	return 0;
}
