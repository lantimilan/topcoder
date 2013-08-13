// CHMOD.cpp

// for each of 1 to 100, can find a list of pos
// given l and r, can find num of 1, 2, ..., 100
// then compute 1^k[1] * 2^k[2] * ... * 100^k[100] % MOD
// can use fastpow

// cin/cout takes 6.643s, maybe too slow
// use scanf/printf
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> pos[105];

int fastpow(int a, int b, int m)
{
    int ans = 1;
    int base = a;
    while (b) {
        if (b & 1) ans = (long long)ans * base % m;
        base = (long long)base * base % m;
        b /= 2;
    }
    return ans;
}

int main()
{
    int N; scanf("%d", &N); //cin >> N;
    for (int i = 0; i < N; ++i) {
        int val; scanf("%d", &val); //cin >> val;
        pos[val].push_back(i+1);
    }

    int T; scanf("%d", &T); //cin >> T;
    while (T--) {
        int ans = 1;
        int L, R, M; scanf("%d%d%d", &L, &R, &M); //cin >> L >> R >> M;
        for (int val = 1; val <= 100; ++val) {
            vector<int>::iterator t1, t2;
            //t1 = lower_bound(pos[val].begin(), pos[val].end(), L);
            //t2 = upper_bound(pos[val].begin(), pos[val].end(), R);
            //int occ = t2 - t1;
            //int occ = N;
            //ans = (long long) ans * fastpow(val, occ, M) % M;
        }
        printf("%d\n", ans); //cout << ans << endl;
    }
}
