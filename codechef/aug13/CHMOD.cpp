// CHMOD.cpp

// for each of 1 to 100, can find a list of pos
// given l and r, can find num of 1, 2, ..., 100
// then compute 1^k[1] * 2^k[2] * ... * 100^k[100] % MOD
// can use fastpow

// cin/cout takes 6.643s, maybe too slow
// use scanf/printf and prefix sum 2.382s, still TLE
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

int cnt[100005][105];
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
int pos[105];
const int LIM = (int)1e9;

int fastpow(int a, int b, int m)
{
    long long ans = 1;
    long long base = a;
    while (b) {
        if (b & 1) ans *= base;
        base *= base;
        if (ans >= LIM) ans %= m;
        if (base >= LIM) base %= m;
        b /= 2;
    }
    return ans % m;
}

int main()
{
    for (int x = 0; x < 25; ++x) pos[primes[x]] = x;
    int N; scanf("%d", &N); //cin >> N;
    for (int v = 1; v <= 100; ++v) cnt[0][v] = 0;
    for (int i = 0; i < N; ++i) {
        for (int v = 1; v <= 100; ++v) cnt[i+1][v] = cnt[i][v];
        int val; scanf("%d", &val); //cin >> val;
        cnt[i+1][val]++;
    }

    int T; scanf("%d", &T); //cin >> T;
    for (int t = 0; t < T; ++t) {
        int L, R, M; scanf("%d%d%d", &L, &R, &M); //cin >> L >> R >> M;
        //cout << "LRM " << L << ' ' << R << ' ' << M << endl;
        long long ans = 1;
        int pcnt[30] = {0};
        for (int v = 2; v <= 100; ++v) {
            int c = cnt[R][v] - cnt[L-1][v];
            int val = v;
            for (int x = 0; x < 25; ++x) {
                int p = primes[x];
                int k = 0;
                if (p*p > val) break;
                while (val % primes[x] == 0) {
                    val /= primes[x]; k++;
                }
                pcnt[x] += c * k;
            }
            if (val > 1) pcnt[pos[val]] += c;
        }
        for (int x = 0; x < 25; ++x) {
            ans *= fastpow(primes[x], pcnt[x], M);
            if (ans >= LIM) ans %= M;
        }
        ans %= M;
        printf("%d\n", (int)ans);
    }
}
// after a lot of hacking, finally AC
// basic idea: count for 1 to 100
// then use fastpow to compute product of exp of 1 to 100
// 1. to count for 1 to 100, can use prefix sum, faster than binary search in
// a list of pos for each of 1 to 100
// 2. to compute exponentiation for 1 to 100, can factor them into primes and
// take the exponentiation for primes, a factor of 4 speed up, since only 25
// primes in 1 to 100
// Correct Answer
// Execution Time: 7.89
// TL
