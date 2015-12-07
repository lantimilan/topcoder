// target.cpp
#include <algorithm>
#include <iostream>
using namespace std;

const int M = 1e4;
long long xy2[500000+5];
long long R2[M+5];

int main() {
    int K, N; cin >> K >> N;
    for (int i = 0; i < K; ++i) {
        long long r; cin >> r;
        R2[i] = r * r;
    }
    sort(R2, R2+K);
    for (int i = 0; i < N; ++i) {
        long long x, y; cin >> x >> y;
        xy2[i] = x*x + y*y;
    }
    sort(xy2, xy2 + N);

    long long score = 0;
    int s = K;
    long long *p1 = upper_bound(xy2, xy2 + N, R2[0]);
    long long *p2;
    score += s * (p1 - xy2);
    for (int i = 1; i < K; ++i) {
        p1 = upper_bound(xy2, xy2 + N, R2[i-1]);
        p2 = upper_bound(xy2, xy2 + N, R2[i]);
        score += (--s) * (p2 - p1);
    }
    cout << score << endl;
}
