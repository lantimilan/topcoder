// utopian-tree.cpp
//
// n     = 0 1 2 3 4  5  6
// f(n)  = 1 2 3 6 7 14 15
// m <- (n+1)/2
// f(m) = 2*f(m-1) + 1
// so f(m) = 2^m - 1
// f(0) = 1
// if n is odd, return f(m)-1

#include <iostream>
using namespace std;

int main()
{
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int m = (n+1) / 2 + 1;
        int ans = (1LL<<m) - 1;
        if (n & 1) ans--;
        cout << ans << endl;
    }
}
