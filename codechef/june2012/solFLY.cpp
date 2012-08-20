/**
 * June 2012 Codechef Long Contest
 *
 * Problem:     FLY
 * Author:      Anton Lunyov (Tester)
 * Complexity:  O(T)
 * Timing:      0.08 out of 2
 */

#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

// the answer is a+b*C, where a, b are integers
// a is the time penalty and b is the number of edges
// C = cI + cF / pw, pw=1e9 and division is in double
// b = b1 * pw + b0
// hence a+b*C = a + (b1*pw+b0)*(cI+cF/pw)
// = a+b1*(cI*pw+cF)+b0*cI + b0*cF/pw
void print(LL a, LL b, int cI, int cF) {
	int pw = 1000000000;
	int b1 = b / pw;
	int b0 = b % pw;
	LL q = a + LL(b1) * (cI * pw + cF) + LL(b0) * cI + LL(b0) * cF / pw;
	int r = LL(b0) * cF % pw;
	printf("%lld.%09d\n", q, r);
}

int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int n,m;
		char s[21];
		cin >> n >> s >> m;

		// finding of cI and cF
		int cI, cF = 0;
		for (int i = 0; s[i]; ++i) {
			if (s[i] == '.') {
				s[i] = 0;
				char *w = s + i + 1;
				sscanf(w, "%d", &cF);
				for (int n = strlen(w); n < 9; ++n) {
					cF*=10;
				}
				break;
			}
		}
		sscanf(s, "%d", &cI);

		// we only care whether we have 4 different vertexes in the input or not
		int L = 2 * m;
		int x[4];
		for (int i = 0; i < L; ++i) {
			cin >> x[i];
		}
		sort(x, x + L);
		L = unique(x, x + L) - x;

		if (L <= 3) {
			// the case when free graph is a subgraph of star graph
			if (cI >= 2) {
				// the optimal model is the star graph
				print(2LL * (n - 1) * (n - 1), n - 1 - m, cI, cF);
			} else {
				// the optimal model is the complete graph
				print(LL(n) * (n - 1), LL(n) * (n - 1) / 2 - m, cI, cF);
			}
		} else {
			// the case of two separate edges say (0,1) and (2,3)
			if (cI >= 2 * (n - 2)) {
				// the optimal way is to connect (0,3), (0,4), ..., (0, N - 1)
				print(2LL * n * (n - 1) - 4, n - 1 - m, cI, cF);
			} else if (cI >= 2) {
				// the optimal way is to connect (0,2), (0,3), ..., (0, N - 1)
				print(2LL * n * (n - 2), n - m, cI, cF);
			} else {
				// the optimal model is the complete graph
				print(LL(n) * (n - 1), LL(n) * (n - 1) / 2 - m, cI, cF);
			}
		}
	}
	return 0;
}
