#include <iostream>
using namespace std;

int A[100000+5];
long long pre[100000+5];

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int i = 0; i < N; ++i) cin >> A[i];
        pre[0] = A[0];
        for (int i = 1; i < N; ++i) {
            pre[i] = pre[i-1] + A[i];
        }
        int days = 0;
        long long sum = 1;
        while (sum < N) {
            sum += pre[sum-1];
            days++;
        }
        cout << days << endl;
    }
}
