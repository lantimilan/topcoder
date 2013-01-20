// N=20, brute force 2^N

#include <iostream>
using namespace std;

int main()
{
    int N; cin >> N;
    int a[30];
    int sum = 0, best;
    for (int i=0; i<N; ++i) cin >> a[i];

    for (int i=0; i<N; ++i) sum += a[i];
    best = sum;
    for (int b=0; b<(1<<N); ++b) {
        int part = 0, diff;
        for (int i=0; i<N; ++i) if (b & 1<<i) part += a[i];
        diff = sum - part - part;
        if (diff < 0) diff = -diff;
        best = min(diff, best);
    }
    cout << best << endl;
}

// 4729970  13:31:01 20 Jan 2013
// lantimilan  1005. Stone Pile    C++ Accepted    0.109   196 KB
//
// easy problem
