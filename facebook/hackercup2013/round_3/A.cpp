// A.cpp
//
// Digits War
//
// C[L][a][b] = sum C[L-1][b][c] for c = 0 to 9 and a,c not conflict
// fastexp

#include <cstring>
#include <iostream>
using namespace std;

typedef long long int64;

const int MOD = 1e9+7;

int M[10][10];
int T[10][10];

void mult(int a[][10][10], int b[][10], int c[][10][10])
{
    int n = 10;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            c[i][j] = 0;
            for (int k=0; k<n; ++k) {
                c[i][j] += a[i][j][k] * b[k][j];
                if (c[i][j] >= MOD) c[i][j] -= MOD;
            }
        }
    }
}

void mult(int a[][10][10], int b[][10][10], int c[][10][10])
{
    int n = 10;

    for (int i=0; i<n; ++i)
    for (int j=0; j<n; ++j)
    for (int k=0; k<n; ++k)
    {
        c[i][j][k] = 0;
        for (int l=0; l<n; ++l) {
            c[i][j][k] += a[i][j][l] * b[l][i][j];
        }
    }
}

void fastexp(int a[][10], int n)
{
    int base[10][10]; memcpy(base, a, sizeof base);
    int ans[10][10]; memset(ans, 0, sizeof ans);

    while (n) {
        int tmp[10][10];
        if (n&1) {
            mult(base, ans, tmp);
            memcpy(ans, tmp, sizeof tmp);
        }
        mult(base, base, tmp);
        memcpy(base, tmp, sizeof tmp);
    }
}

void solve()
{
    long long K; cin >> K;
    for (int i=0; i<10; ++i)
    for (int j=0; j<10; ++j) {
        cin >> M[i][j];
        T[i][j] = 1 - M[i][j];
    }
    int coeff[10][10][10];  // first, third, second due to matrix mult rule
    for (int i=0; i<10; ++i)
    for (int k=0; k<10; ++k)
    for (int j=0; j<10; ++j)
        coeff[i][k][j] = T[i][k];

    int final[10][10][10];
    int ans[10][10];
    fastexp(coeff, K-1, final);
    mult(final, T, ans);
    int64 kans = 0;
    for (int i=0; i<10; ++i)
    for (int j=0; j<10; ++j) {
        kans = kans + ans[i][j];
        if (kans >= MOD) kans -= MOD;
    }
    cout << kans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--) solve();
}
