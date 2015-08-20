// campers.cpp
// greedy

#include <iostream>
using namespace std;

int A[2000000+5];

int main() {
    int N, K; cin >> N >> K;
    for (int i = 0; i < K; ++i) {
        int val; cin >> val;
        A[val] = 1;
    }

    for (int x = 1; x <= N; ++x) {
        if (A[x-1] == 0 && A[x+1] == 0) A[x] = 1;
    }

    int ans = 0;
    for (int x = 1; x <= N; ++x) ans += A[x];
    cout << ans << endl;
}

