// CHEFADD.cc
#include <iostream>
using namespace std;

int count_bit(int k) {
    int ans = 0;
    while (k) {
        ans++;
        k &= k-1;
    }
    return ans;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int A, B, C; cin >> A >> B >> C;
        int bitsA = count_bit(A);
        int bitsB = count_bit(B);
        int ans = 0;
        for (int a = 1; a < C; ++a) {
            int b = C - a;
            if (count_bit(a) == bitsA && count_bit(b) == bitsB) {
                ans++;
            }
        }
        cout << ans << endl;
    }
}
