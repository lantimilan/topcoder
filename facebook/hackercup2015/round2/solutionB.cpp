#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

const int N = 20;

long double E[N+1];

int main(void) {
  int TC;
  scanf("%d", &TC);
  for (int tp = 1; tp <= TC; ++tp) {
    long double p;
    scanf("%Lf", &p);

    E[0] = 0;
    FOR(n, 1, N+1) {
      E[n] = 1;
      double fail = 1;
      REP(i, n) fail *= 1 - p;

      FOR(k, 1, n+1) {
        llint ways = 1;
        for (int i = n; i > n-k; --i) ways *= i;
        for (int i = 1; i <= k; ++i) ways /= i;
        long double prob = 1;
        REP(i, n)
          if (i < k) prob *= p; else
            prob *= 1 - p;
        E[n] += ways * prob * E[n-k];
      }
      E[n] /= (1 - fail);
    }

    printf("Case #%d: ", tp);
    printf("%.5Lf\n", E[N]);
  }
  return 0;
}
