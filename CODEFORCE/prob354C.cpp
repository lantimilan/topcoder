// prob354C.cpp
//
// given an array a[0..n) for n = 3*10^5, with a[i] > 0
// and integer k
// you can decrease each a[i] by no more than k, to obtain b[i] > 0
// the problem asks you to maximize the gcd of b[0..n)
//
// Solution: the best you can have is min of a[0..n)
// and it is easy to see that if you can obtain d as gcd, then you
// can also obtain d-1, because to reduce a[i] to b[i], you have a
// budget of k, and you only need to deal with a gap of at most d
// this implies a binary search for the desired d
//
// TODO:
// ? Could it be faster?

#include <iostream>
using namespace std;

int A[300000+5];
int n, k;

bool check(int divisor)
{
    for (int i = 0; i < n; ++i)
        if (A[i] % divisor > k) {
            return false;
        }
    return true;
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> A[i];

    /*
    int lo = 1, hi = A[0]+1;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        cout << "mid " << mid << endl;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    */
    int lo;
    for (lo = A[0]; lo > 0; --lo)
        if (check(lo)) break;
    cout << lo << endl;
}
