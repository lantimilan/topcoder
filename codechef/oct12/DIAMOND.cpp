// codechef

#include <cstdio>
using namespace std;

const int MAXN = 2000;
double prob[MAXN+5][MAXN+5];

void init()
{
	prob[0][0] = 1;
	for(int i=1; i<MAXN; ++i) {
		prob[i][0] += 1.0/2;
		prob[i][i] += 1.0/2;
		// 1/4 [l+1, r-1]
		// 1/4 [l+2, r]
		// 1/4 [l+1, r-1]
		// 1/4 [l, r-2]
		for(int j=1; j<i; ++j) {
			prob[i][j] += 1.0/4 * prob[i-2][j-1];
		}
		for(int j=2; j<=i; ++j) {
			prob[i][j] += 1.0/4 * prob[i-2][j-2];
		}
		for(int j=1; j<i; ++j) {
			prob[i][j] += 1.0/4 * prob[i-2][j-1];
		}
		for(int j=0; j<i-1; ++j) {
			prob[i][j] += 1.0/4 * prob[i-2][j];
		}
	}	
	/*for(int i=0; i<6; ++i) {
		double sum = 0;
		for(int j=0; j<=i; ++j) {
			printf("%.5lf ", prob[i][j]);
			sum += prob[i][j];
		}
		printf("\tsum %.5lf", sum);
		putchar('\n');
	}*/		
}

void solve()
{
	int N; scanf("%d", &N);
	int val[2005];
	for(int i=0; i<N; ++i) {
		scanf("%d", val + i);
	}
	double sum = 0;
	for(int i=0; i<N; ++i) {
		sum += prob[N-1][i] * val[i];
	}
	printf("%.3lf\n", sum);
}

int main()
{
	init();
	int T; scanf("%d", &T);
	while(T--) solve();
}

// Correct Answer 
// Execution Time: 6.49 