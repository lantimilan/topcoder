// homework.cpp
#include <iostream>
using namespace std;

const int MM = 10000000;
const int M = 10000;
bool isprime[M];
int primes[M];
int P;
int primacity[MM+5];

void init()
{
    for (int i = 0; i < M; ++i) isprime[i] = true;
    isprime[0] = isprime[1] = false;
    P = 0;
    for (int k = 2; k < M; ++k) if (isprime[k]) {
        primes[P++] = k;
        for (int j = k * k; j < M; j += k) {
            isprime[j] = false;
        }
    }
    /*
    for (int i = 0; i < 20; ++i) {
        cout << primes[i] << ' ';
    } cout << endl;
    */

    primacity[0] = primacity[1] = 0;
    for (int i = 2; i <= MM; ++i) {
        int val = i;
        int cnt = 0;
        for (int x = 0; x < P; ++x) {
            int p = primes[x];
            if (p * p > val) break;
            if (val % p == 0) cnt++;
            while (val % p == 0) val /= p;
        }
        if (val > 1) cnt++;
        primacity[i] = cnt;
    }
    /*
    for (int i = 0; i < 50; ++i) {
        cout << MM-i << ' ' << primacity[MM-i] << endl;
    }
    */
}

void solve(int tcase)
{
    int A, B, K; cin >> A >> B >> K;
    int ans = 0;
    for (int i = A; i <= B; ++i) {
        if (primacity[i] == K) ans++;
    }
    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

int main()
{
    init();
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
