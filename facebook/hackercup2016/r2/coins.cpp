// coins.cpp
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

double comb[3005][3005];
double prob[3005];  // (N, K)
double succ[3005], fail[3005];
int N, K;
double P;

void init() {
    comb[0][0] = 1;
    for (int n = 1; n <= 3000; ++n) {
        comb[n][0] = comb[n][n] = 1;
        for (int r = 1; r < n; ++r) {
            comb[n][r] = comb[n-1][r-1] + comb[n-1][r];
        }
    }
    for (int i = 0; i < 10; ++i) {
    for (int j = 0; j <= i; ++j) {
        cout << comb[i][j] << ' ';
    }
    cout << endl;
    }
    cout << comb[3000][1000] << endl;
}

void calc() {
    succ[0] = fail[0] = 1.0;
    for (int i = 1; i <= N; ++i) {
        succ[i] = succ[i-1] * P;
        fail[i] = fail[i-1] * (1-P);
    }
    for (int n = 1; n <= N; ++n) {
    prob[n] = 0;
    for (int j = K; j <= n; ++j) {
        //prob[n] += comb[n][j] * pow(P, j) * pow(1-P, n-j);
        prob[n] += comb[n][j] * succ[j] * fail[n-j];
    }
    }
}

void chmax(double &a, double b) {
    if (a < b) a = b;
}

void solve(int tcase) {
    cin >> N >> K >> P;
    calc();

    double best = 0;
    for (int s = 1; s <= N; ++s) {
        int m = N / s;
        int r = N % s;
        double t = m * prob[s] + prob[r];
        if (t > best) {
            cout << "better " << s << ' ' << t << endl;
        }
        chmax(best, t);
    }
    // output
    cout << "Case #" << tcase << ": ";
    cout << fixed << setprecision(9) << best << endl;
}

int main() {
    init();
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
