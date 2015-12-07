// primedist.cpp
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

const int M = 100000;
bool isprime[M+5];
int primes[M];
int P;
int A[M+5];

void init() {
    for (int i = 0; i <= M; ++i) { isprime[i] = true; }
    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= M; ++i) if (isprime[i]) {
        primes[P++] = i;
        for (int j = i+i; j <= M; j += i) {
            isprime[j] = false;
        }
    }
    /*
    for (int i = 0; i < 20; ++i) {
        cout << primes[i] << ' ';
    }
    cout << endl;
    */
}

int main() {
    init();

    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<int> pos; pos.push_back(0);
    for (int i = 0; i < P; ++i) {
        int p = primes[i];
        if (p >= N) break;
        pos.push_back(p);
    }
    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        assert(!pos.empty());
        long long sum = 0;
        for (int p : pos) {
            sum += A[p];
        }
        sum -= 1LL * A[pos[0]] * pos.size();
        ans += sum;
        for (int &p : pos) {
            p++;
        }
        while (!pos.empty() && pos.back() >= N) pos.pop_back();
    }
    cout << ans << endl;
}
