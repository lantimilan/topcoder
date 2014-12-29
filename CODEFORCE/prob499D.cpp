// prob499D.cpp
// state: dp[i][j] expected number of guessed songs for the first i songs
// and just before j-th second
// dp[i][j] can move into dp[i+1][j+1] ... dp[i+1][j+t[i]-1]
//
// the part I was confused is to realize the Bernoulli process
// keep trying until succeed, with p = p[i]
// and stop at t[i] seconds

#include <iostream>
#include <iomanip>
using namespace std;

double dp[5005][5005];
int prob[5005];
int stop[5005];

void chmax(double &d1, double d2)
{
    if (d1 < d2) d1 = d2;
}

int main()
{
    int n, T; cin >> n >> T;
    for (int i = 0; i < n; ++i) {
        cin >> prob[i] >> stop[i];
    }
    for (int i = 0; i <= n; ++i)
    for (int t = 0; t <= T; ++t) {
        dp[i][t] = 0;
        if (i > 0 && t < T) {  // from song - 1
            double next;
            if (t >= stop[i-1]) {
                next = dp[i-1][t] + 1;
            } else {
                next = dp[i-1][t] + prob[i-1] / 100.0;
            }
            chmax(dp[i][t], next);
        }
        if (t > 0) {
            chmax(dp[i][t], dp[i][t-1]);
        }
    }
    cout << fixed << setprecision(9) << dp[n][T] << endl;
}

