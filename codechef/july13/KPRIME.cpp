// KPRIME.cpp

#include <iostream>
using namespace std;

const int M = 100000;

bool isprime[M+1];
int primes[M];
int P;
int dp[M+1][6];  // cap, num-prime-factor

void init()
{
    for (int i = 2; i <= M; ++i) isprime[i] = true;
    for (int i = 2; i <= M; ++i) if (isprime[i]) {
        primes[P++] = i;
        for (int j = i+i; j <= M; j += i) isprime[j] = false;
    }
    for (int k = 1; k <= M; ++k) {  // precompute
        for (int f = 1; f <= 5; ++f) dp[k][f] = dp[k-1][f];
        int val = k;
        int pfactor = 0;
        for (int x = 0; x < P; ++x) {
            int pm = primes[x];
            if (isprime[val]) { pfactor++; val = 1; break; }
            if (val % pm == 0) {
                pfactor++;
                while (val % pm == 0) val /= pm;
            }
            if (val == 1) break;
        }
        if (pfactor <= 5) dp[k][pfactor]++;
    }
}

int main()
{
    init();
    int T; cin >> T;
    while (T--) {
        int A, B, K; cin >> A >> B >> K;
        int ans = dp[B][K] - dp[A-1][K];
        cout << ans << endl;
    }
}
