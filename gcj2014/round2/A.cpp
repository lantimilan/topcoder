// A.cpp
//
// sort by size
// then greedy pack two files into one disc

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    int N; cin >> N;
    int X; cin >> X;
    vector<int> S(N);
    for (int i = 0; i < N; ++i) cin >> S[i];
    sort(S.begin(), S.end());
    int disc = 0;
    int lo, hi;
    for (lo = 0, hi = S.size()-1; hi >= lo; --hi) {
        if (S[hi] + S[lo] <= X) { ++lo; ++disc; }
        else { ++disc; }
    }
    cout << disc << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
