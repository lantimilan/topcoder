// lazy_sort_simulate.cpp
//
// simulate the process, at any time, the segment already built
// must be contiguous

#include <algorithm>
#include <iostream>
using namespace std;

bool check(int A[], int v, int begin, int end)
{
    int lo, hi; lo = hi = v;
    while (begin <= end) {
        if (A[begin] == lo - 1) {
            --lo; ++begin;
        } else if (A[begin] == hi + 1) {
            ++hi; ++begin;
        } else if (A[end] == lo - 1) {
            --lo; --end;
        } else if (A[end] == hi + 1) {
            ++hi; --end;
        } else {
            return false;
        }
    }
    return true;
}

void solve(int tcase)
{
    int A[50000+5];
    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];

    bool ans = false;
    if (check(A, A[0], 1, N-1)) ans = true;
    else {
        reverse(A, A+N);
        ans = check(A, A[0], 1, N-1);
    }
    // output sol
    cout << "Case #" << tcase << ": ";
    // sol here
    cout << (ans ? "yes" : "no");
    cout << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
