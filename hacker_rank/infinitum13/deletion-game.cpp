// deletion-game.cpp
#include <cstdlib>
#include <iostream>
using namespace std;
// A + B = S
// A - B = K
// S = sum_i=1^N i
// K is yes iff S and K are same parity
// because 1..N can sum to any number between 1 and S

int main() {
    int T; cin >> T;
    while (T--) {
        long long N, K; cin >> N >> K; K = abs(K);
        long long S = (N+1) * N / 2;
        bool good = (K <= S) && ((S & 1) == (K & 1));
        cout << (good ? "YES" : "NO") << endl;
    }
}
