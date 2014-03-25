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

set<int> X;
set<int> Y;

int main()
{
    const int M = 1e6;
    int n; scanf("%d", &n);
    int m = n; printf("%d\n", m);
    for (int i = 0; i < n; ++i) {
        int x; scanf("%d", &x);
        X.insert(x);
    }
    set<int>::iterator it;
    for(it = X.begin(); it != X.end(); ++it) {
        int v = *it;
        int v2 = M + 1 - v;
        if (!X.count(v2)) { Y.insert(v2); }
    }
    assert(Y.size() <= m);
    if (Y.size() < m) for (int i = 1; i <= M; ++i) {
        if (!X.count(i) && !X.count(M+1-i)) {
            Y.insert(i);
            Y.insert(M+1-i);
        }
        if (Y.size() >= m) break;
    }
    assert(Y.size() == m);
    for (it = Y.begin(); it != Y.end(); ++it) {
        if (it != Y.begin()) putchar(' ');
        printf("%d", *it);
    }
    putchar('\n');
}
