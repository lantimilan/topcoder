// =========================================================
// 
//       Filename:  prob283D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  03/22/2013 01:48:24 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/22/2013, LI YAN
// 
// =========================================================

// if (x, y) is a cool pair
// then x = (a + b)/2 * y for some integer a and b
// so as long as x * 2 is a multiple of y, we are good
//
// then the final sequence looks like
// a1, a2, ..., a_n
// and a1*2 is a multiple of a2
// a2*2 is a multiple of a3
// ...
// a_n-1 * 2 is a multiple of a_n
//
// find the longest subsequence of this condition
// and the rest need to be changed
//
// there is one catch:
// let the consecutive sequence be k, k+1, ..., k+y-1
// then (2k + y-1) * y = 2*x
// notice that if y is even, then 2k + y-1 must be odd
// and hence 2*x / y must be odd

#include <algorithm>
#include <iostream>
using namespace std;

typedef long long int64;

int64 a[5005];
int64 val[5005][60];
int d[5005];

int log2(int64 x)
{
    int ans = 0;
    while (x % 2 == 0) {
        ans++; x /= 2;
    }
    return ans;
}

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0; i < n; ++i) {
        int64 k = a[i];
        int j = 0; val[i][j] = a[i];
        while (k % 2 == 0) {
            k /= 2;
            val[i][++j] = k;
        }
        while (++j < 60) val[i][j] = k;
    }
    d[0] = 1;
    for (int i = 1; i < n; ++i) {
        int prev = 0;
        for (int j = i-1; j >= 0; --j) {
            int dist = min(i - j, 60-1);  // index out of bounds here without min
            if (a[j] % val[i][dist] == 0) {
                if (a[i] % 2 == 1) { 
                    prev = max(prev, d[j]);
                } else {
                    if (log2(a[j]) < log2(a[i])) {
                        cout << a[j] << ' ' << log2(a[j])
                            << ' ' << a[i] << ' ' << log2(a[i]) << endl;
                        prev = max(prev, d[j]);
                    }
                }
            }
        }
        d[i] = 1 + prev; //cout << i << ' ' << d[i] << endl;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, d[i]);
    }
    cout << n - ans << endl;
}
