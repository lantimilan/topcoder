// B.cpp
// the desired configuration is that, adjacent rows either match or flip
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int N, M, K;

int a[105][105];
int b[105][105];

void chmin(int &a, int b)
{
    if (a < 0 || a > b) a = b;
}

// if NROW > budget_K, then at least one row is unchanged
int solve_big()
{
    int ans = -1;
    for (int candidate = 0; candidate < N; ++candidate) {
        int cost = 0;
        for (int i = 0; i < N; ++i) if (i != candidate)
        {
            int zero = 0, one = 0;
            for (int j = 0; j < M; ++j) {  // must match
                int c1 = b[candidate][j];
                int c2 = b[i][j];
                if (c1 != c2) zero++;
            }
            for (int j = 0; j < M; ++j) {  // must flip
                int c1 = b[candidate][j];
                int c2 = b[i][j];
                if (c1 == c2) one++;
            }
            cost += min(zero, one);
        }
        chmin(ans, cost);
    }
    return ans;
}

int solve_mask()
{
    int ans = -1;
    for (int mask = 0; mask < (1 << M); ++mask) {
        int cost = 0;
        for (int j = 0; j < M; ++j) {
            if (1<<j & mask) {
                b[0][j] = 1 - b[0][j];
                cost++;
            }
        }
        for (int i = 1; i < N; ++i) {
            int zero = 0, one = 0;
            for (int j = 0; j < M; ++j) {  // must match
                int c1 = b[0][j];
                int c2 = b[i][j];
                if (c1 != c2) zero++;
            }
            for (int j = 0; j < M; ++j) {  // must flip
                int c1 = b[0][j];
                int c2 = b[i][j];
                if (c1 == c2) one++;
            }
            cost += min(zero, one);
        }
        chmin(ans, cost);
    }
    return ans;
}

int main()
{
    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
        cin >> a[i][j];

    if (N < M) {  // transpose
        for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            b[j][i] = a[i][j];
        swap(N, M);
    } else {
        for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            b[i][j] = a[i][j];
    }

    int ans;
    if (N <= K) {  // during contest, wrote < instead of <=, failed Case #60
        ans = solve_mask();
    } else {
        ans = solve_big();
    }
    if (ans <= K) cout << ans << endl;
    else cout << -1 << endl;
}
