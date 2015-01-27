// all_critical_recursive.cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int N = 20;
double comb[25][25];

void init()
{
    for (int n = 0; n <= N; ++n) {
        comb[n][0] = comb[n][n] = 1;
        for (int r = 1; r < n; ++r) {
            comb[n][r] = comb[n-1][r-1] + comb[n-1][r];
        }
    }
    /*
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j <= i; ++j) cout << comb[i][j] << ' ';
        cout << endl;
    }
    */
}

void solve(int tcase)
{
    double p; cin >> p; //cout << p << endl;
    double E[25];

    E[0] = 0;
    for (int n = 1; n <= N; ++n) {
        E[n] = 1;
        for (int k = 1; k < n; ++k) {
            double prob = 1.0;
            for (int i = 0; i < n; ++i) {
                if (i < k) prob *= p;
                else prob *= 1-p;
            }
            E[n] += comb[n][k] * prob * E[n-k];
        }
        double fail = 1.0;
        for (int i = 0; i < n; ++i) fail *= 1-p;
        E[n] /= (1 - fail);
    }
    // output solution
    cout << "Case #" << tcase << ": ";
    // sol here
    cout << E[N];
    cout << endl;
}

int main()
{
    init();
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
