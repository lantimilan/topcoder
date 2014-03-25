// prob406B.cpp
//
// problem: given s=10^6, and a set of X in {1,...,1000000}
// find a set of Y such that sum_{y in Y} {s - y} = sum_{x in X} (x-1)
//
// the hidden fact is that, X has at most 5x10^5 elements, in other
// words, X has size no more than half of 10^6.
// So this solution will work:
// for each y in Y such that 1000000+1 - y is not in Y, we include that number
// in X
// for those pairs in Y such that their sum is 1000000+1, we include another
// pair not in Y with sum 1000000+1, in X
//
// the trick for this problem is that X has at most half of the elements

#include <cassert>
#include <cstdio>
#include <set>
using namespace std;

const int M = 1e6;
int used[M+1];
int ans[M+1];

int main()
{
    int n; scanf("%d", &n);
    int m = n; printf("%d\n", m);
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        used[x] = 1;
    }
    for (int i = 1; i <= M; ++i) {
        if (used[i] && !used[M+1-i]) {
            ans[--m] = M+1-i;
            used[M+1-i] = 1;
        }
    }
    for (int i = 1; i <= M; ++i) if (m > 0) {
        if (!used[i]) {
            ans[--m] = i;
            ans[--m] = M+1-i;
            used[i] = used[M+1-i] = 1;
        }
    }
    for (int i = 0; ans[i]; ++i) {
        if (i) putchar(' ');
        printf("%d", ans[i]);
    }
    putchar('\n');
}
