// FDIVGAME.cc
//
// mex(n) = minimum exclusive in {0, 1, 2, ...}

#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

long long mex(long long val) {
    switch (val) {
        case 0: return 0;
        case 1: return 1;
        case 2: return 2;
        case 3: return 2;  // next can be 3/2 = 1 to 3/6 = 0
        case 4: return 3;  // next can be 4/2 = 2 to 4/6 = 0
        case 5: return 3;  // next can be 5/2 = 2 to 5/6 = 0
        // for val >= 6, next can be val/6 >= 1 to val/2
        // No, this is wrong!!
        // write ranges for 0, 1, 2, 3 and observe that val get incremented
        // at a period of 12
        // Indeed, the first few small values are
        // [0, 1, 2, 2, 3, 3, 0, 0, 0, 0, 0, 0] so it is tempting to make an
        // incorrect guess that mex[n] = 0 for n >= 6.
        default: return mex(val/12);
    }
}

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        long long sum = 0;
        for (int i = 0; i < N; ++i) {
            long long k; cin >> k;
            sum ^= mex(k);
        }
        // string ans = (sum == 0) ? "Derek" : "Henry";
        // cout << ans << endl;
        puts((sum == 0) ? "Derek" : "Henry");
    }
}
// TLE
// WA
