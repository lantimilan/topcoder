// budget-friendly.cpp
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

int nhotel[15];
int price[15][105];
double score[15][105];
double best[15][10000+5];

double knapsack(int n, int budget) {
    if (budget < 0 || n == 0) return 0;
    if (best[n][budget] >= 0) {
        return best[n][budget];
    }
    double curr = 0;
    for (int h = 0; h < nhotel[n-1]; ++h) {
        int p = price[n-1][h];
        double s = score[n-1][h];
        if (budget - p >= 0) {
            double next = knapsack(n-1, budget - p);
            if ((next == 0 && n-1 == 0) || next > 0) {
                curr = max(curr, next + s);
            }
        }
    }
    return best[n][budget] = curr;
}

int main() {
    int C, B; cin >> C >> B;
    for (int i = 0; i < C; ++i) {
        cin >> nhotel[i];
        for (int j = 0; j < nhotel[i]; ++j) cin >> price[i][j] >> score[i][j];
    }
    memset(best, -1, sizeof best);

    double ans = knapsack(C, B);
    if (ans == 0) cout << -1 << endl;
    else cout << fixed << setprecision(2) << ans << endl;
}
