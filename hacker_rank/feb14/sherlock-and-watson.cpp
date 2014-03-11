// sherlock-and-watson.cpp
//
// A[i] -> A[i+K % N]

#include <iostream>
using namespace std;

int A[100000+5];

int main()
{
    int N, K, Q; cin >> N >> K >> Q;
    for (int i = 0; i < N; ++i) cin >> A[i];

    for (int q = 0; q < Q; ++q) {
        int x; cin >> x;
        x = (x - K) % N;
        if (x < 0) x += N;
        cout << A[x] << endl;
    }
}
