#include <iostream>
using namespace std;

int A[100000+5];
int B[100000+5];

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int i = 0; i < N; ++i) cin >> A[i];
        for (int i = 0; i < N; ++i) cin >> B[i];
        bool good = true;
        for (int i = 0; i < N; ++i) {
            int d = B[i] - A[i];
            if (d < 0) { good = false; break; }
            else if (d == 0) { /* do nothing */ }
            else {
                if (i + 2 >= N) { good = false; break; }
                A[i] += d;
                A[i+1] += d * 2;
                A[i+2] += d * 3;
            }
        }
        cout << (good ? "TAK" : "NIE") << endl;
    }
}
