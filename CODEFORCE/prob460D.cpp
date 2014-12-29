// prob460D.cpp
//
// let n = r - l + 1
// if n == k, then we have to use all l..r
// else n > k
// 1. k = 1, then use minval, which is l
// 2. k = 2, then we know n is at least 3, then we can find even,
// and even+1 to get 1
// 3. k = 3, we know we can get 1 for sure, because we have the option to
// use even, even+1
// now the problem becomes whether we can get 0
// if we have some number in [l..r] which ends with 01 in lsb,
// then we can use 01, 10, 11 to obtain 0
// the worst case is l is 10, then we know that if n is at least 6, we have
// 10, 11, 00, 01, 10, 11, and ans must be 0
// else n <= 5 and we can try all triples
// 4. k >= 4, now we know n is at least 5, then we can find even, even+1,
// even+2, even+3, to obtain 0

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    long long l, r;
    int k;
    cin >> l >> r >> k;

    long long n = r - l + 1; assert(n >= k);

    vector<long long> vec;
    long long ans = 0;
    if (k == n) {
        for (long long i = l; i <= r; ++i) ans ^= i;
        for (long long i = l; i <= r; ++i) {
            vec.push_back(i);
        }
    } else {
        if (k == 1) {
            ans = l;
            vec.push_back(l);
        } else if (k == 2) {
            ans = 1;
            long long first = l; if (first & 1) ++first;
            vec.push_back(first);
            vec.push_back(first + 1);
        } else if (k == 3) {
            if (n >= 6) {
                ans = 0;
                long long first = l;
                while ((first & 3) != 1) ++first;
                for (int x = 0; x < 3; ++x) vec.push_back(first + x);
            } else {
                ans = 1;
                long long first = l; if (first & 1) ++first;
                vec.push_back(first);
                vec.push_back(first + 1);
                long long p[3];
                for (p[0] = l; p[0] <= r; ++p[0])
                for (p[1] = p[0]+1; p[1] <= r; ++p[1])
                for (p[2] = p[1]+1; p[2] <= r; ++p[2]) {
                    long long val = p[0] ^ p[1] ^ p[2];
                    if (val == 0) {
                        ans = 0;
                        vec.clear();
                        vec.push_back(p[0]);
                        vec.push_back(p[1]);
                        vec.push_back(p[2]);
                        goto done;
                    }
                }
                done:
                ;
            }
        } else {  // k >= 4
            ans = 0;
            long long first = l; if (first & 1) ++first;
            for (int x = 0; x < 4; ++x) {
                vec.push_back(first + x);
            }
        }
    }
    cout << ans << endl;
    cout << vec.size() << endl;
    for (int x = 0; x < vec.size(); ++x) {
        if (x) cout << ' ';
        cout << vec[x];
    }
    cout << endl;
}
