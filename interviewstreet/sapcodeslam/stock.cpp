#include <cassert>
#include <cmath>
#include <cstdio>
using namespace std;

int N, D;
int prices[1000000+5];
int days[1000000+5];
int points[1000000+5];

bool check(int l, int r) {
	assert(l<r);
	double slope = 1.0*(prices[r] - prices[l]) / (r-l); 
	double intercept;
	intercept = prices[r] - slope * r;
	for(int i=l+1; i<r; ++i) {
		double yexp = slope * i + intercept;
		if (fabs(yexp - prices[i]) > D) return false;
	}
	return true;
}

int main()
{
	scanf("%d%d", &N, &D);
	for(int i=0; i<N; ++i) {
		int day, price;
		scanf("%d%d", &day, &price);
		prices[i] = price;
	}
	int K=0;
	int s=0;
	while(s<N-1) {
		//printf("s %d\n", s);
		days[K] = s+1;
		points[K] = prices[s];
		K++;
		int next;
		int gap;
		bool good = true;
		for(gap = 1; ; gap *= 2) {
			next = s + gap;
			if (next >= N) { next = N-1; }
			if (!check(s, next)) { good = false; break; }
			if (next == N-1) break;
		}
		if (!good) {
			int lo = s + gap/2, hi = s + gap;
			while(lo <= hi) {
				int m = (lo + hi)/2;
				if (check(s, m)) {
					next = m; lo = m+1;
				} else {
					hi = m-1;
				}
			}
		}
		assert(next > s);
		s = next;
	}
	assert(days[K-1] < N);
	days[K] = N; points[K] = prices[N-1]; K++;
	printf("%d\n", K);
	for(int i=0; i<K; ++i)
		printf("%d %d\n", days[i], points[i]);
}

// Score: 0.517241 