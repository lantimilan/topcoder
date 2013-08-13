// SPCANDY.cpp

#include <iostream>
using namespace std;

typedef long long int64;

int main()
{
    int T; cin >> T;
    while (T--) {
        int64 N, K; cin >> N >> K;
        if (K) cout << N/K << ' ' << N%K << endl;
        else cout << 0 << ' ' << N << endl;
    }
}
