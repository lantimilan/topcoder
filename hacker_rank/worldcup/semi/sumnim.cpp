// sumnim.cpp
#include <cassert>
#include <iostream>
#include <map>
using namespace std;
// N=20 is easy, use 1<<20 to generate all possible mask of operations
// need to convert original array into an array with bitwise xor to non-zero
//
// N=36, meet in the middle

map<int, int> myleft;
map<int, int> myright;

int main() {
    int N; cin >> N;
    int A[40];
    for (int i = 0; i < N; ++i) cin >> A[i];

    long long ans = 0;
    int begin = min(N, 18);
    for (int l = begin; l <= N; ++l) {
        int r = N - l;
        myleft.clear(); myright.clear();

        for (int b = 0; b < (1<<begin-1); ++b) {
            int last;
            for (last = begin-1; last >= 0; --last) {
                if (b & 1<<last) break;
            }
            int sum = 0;
            for (int p = last+1; p < l; ++p) sum += A[p];
            int curr = 0;
            for (int i = 0; i <= last; ++i) {
                curr += A[i];
                if (b & 1<<i) {  // hit a separator
                    sum ^= curr;
                    curr = 0;
                }
            }
            //cout << "left " << b << ' ' << sum << endl;
            myleft[sum]++;
        }
        if (r == 0) {
            ans += myleft[0];
        } else {
            for (int b = 0; b < (1<<r-1); ++b) {
                int mask = b | 1<<r-1;
                int sum = 0;
                int curr = 0;
                for (int i = 0; i < r; ++i) {
                    curr += A[l+i];
                    if (mask & 1<<i) {
                        sum ^= curr;
                        curr = 0;
                    }
                }
                myright[sum]++;
            }
            for (auto &kv : myleft) {
                //cout << l << ' ' << r << ": ";
                //cout << kv.first << ' ' << kv.second << ' ' << myright[kv.first] << endl;
                ans += 1LL * myright[kv.first] * kv.second;
            }
        }
    }
    cout << ans << endl;
}
