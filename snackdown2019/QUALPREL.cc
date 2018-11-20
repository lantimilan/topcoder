#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

int A[100000+5];

int main() {
  int T; cin >> T;
  for (int t = 0; t < T; ++t) {
    int N, K; cin >> N >> K;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N, greater<int>());
    int cutoff = A[K-1];
    int ans = K;
    for (int i = K; i < N && A[i] == cutoff; ++i) {
        ++ans;
    }
    cout << ans << endl;
  }
}
