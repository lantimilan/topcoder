#include <cstdio>
#include <algorithm>

using namespace std;

const long long MOD = 1000000007;

long long bin[20], oct[20], c[20];

int lucky(int d) {
  return d == 4 || d == 7 ? 1 : 0;
}

void gen(int len, long long base, long long rem, int cnt) {
  int digit = rem / base % 10;
  for (int i = 0; i < digit; ++i) {
    for (int j = 0; j < (1 << len); ++j) {
      int k = __builtin_popcount(j);
      c[cnt + lucky(i) + k] += bin[k] * oct[len - k];
    }
  }
  if (len > 0) {
    gen(len - 1, base / 10, rem % base, cnt + lucky(digit));
  }
}

long long gao(int n, int m, long long cnt) {
  if (n == 0) {
    return cnt;
  } else {
    long long ret = 0;
    for (int i = 0; i < m; ++i) {
      if (c[i] > 0) {
        --c[i];
        ret += gao(n - 1, m - i, cnt * (c[i] + 1) % MOD);
        ++c[i];
      }
    }
    return ret % MOD;
  }
}

int main() {
  int m;
  long long ans;

  scanf("%d", &m);
  bin[0] = oct[0] = 1;
  for (int i = 1; i < 20; ++i) {
    bin[i] = bin[i - 1] * 2;
    oct[i] = oct[i - 1] * 8;
  }
  gen(10, 10000000000LL, m + 1, 0);
  --c[0];

  ans = 0;
  for (int i = 1; i < 10; ++i) {
    if (c[i] > 0) {
      ans += gao(6, i, c[i]);
    }
  }
  printf("%d\n", (int)(ans % MOD));

  return 0;
}
