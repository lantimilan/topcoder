// prob551D.cpp
#include <iostream>
using namespace std;

unsigned long long N, K;
int L, M;
int mat[2][2];
int pow2;

int fastpow(int base, long long expo) {
    int ans = 1;
    int factor = base;
    while (expo) {
        if (expo & 1) {
            ans = 1LL * ans * factor % M;
        }
        factor = 1LL * factor * factor % M;
        expo /= 2;
    }
    return ans;
}

void mat_copy(int target[2][2], int source[2][2]) {
    for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
        target[i][j] = source[i][j];
}

void mat_mult(const int m1[2][2], const int m2[2][2], int m3[2][2]) {
    for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j) {
        m3[i][j] = 0;
        for (int k = 0; k < 2; ++k) {
            m3[i][j] += 1LL * m1[i][k] * m2[k][j] % M;
            if (m3[i][j] >= M) m3[i][j] -= M;
        }
    }
}

void mat_pow(int base[2][2], long long expo, int res[2][2]) {
    int factor[2][2]; mat_copy(factor, base);
    res[0][0] = res[1][1] = 1;
    res[0][1] = res[1][0] = 0;
    while (expo) {
        int tmp[2][2];
        if (expo & 1) {
            mat_mult(res, factor, tmp);
            mat_copy(res, tmp);
        }
        expo /= 2;
        mat_mult(factor, factor, tmp);
        mat_copy(factor, tmp);
    }
}

void init() {
    int base[2][2]; base[0][0] = base[0][1] = base[1][0] = 1; base[1][1] = 0;
    mat_pow(base, N-1, mat);
    pow2 = fastpow(2, N);
}

int main() {
    cin >> N >> K >> L >> M;

    // K must be unsigned because 1<<63 does not fit in long long
    if (L < 64 && K >= (1LL << L)) {  // max is 2^L -1
        cout << 0 << endl; return 0;
    }

    init();
    long long ans = 1LL % M;  // must have this or M = 1 breaks
    for (int b = 0; b < L; ++b) {
    // let dp[n][0] be number of bit string of length n with no consecutive
    // ones and end up with 0, similarly define dp[n][1]
    // then
    // dp[n][0] = dp[n-1][0] + dp[n-1][1] if we append bit 0 to (n-1)-bit string
    // dp[n][1] = dp[n-1][0] because we can only append 1 to (n-1)-bit string
    // ending with 0
    // now we can do matrix fast mult trick
    // | f(n,0) | = |1 1| | f(n-1,0) |
    // | f(n,1) |   |1 0| | f(n-1,1) |
    //cout << mat[0][0] << mat[0][1] << mat[1][0] << mat[1][1] << endl;
    int cnt = (1LL*mat[0][0] + mat[0][1] + mat[1][0] + mat[1][1]) % M;
    //cout << "cnt " << cnt << endl;
    int curr;
    if (K & (1LL << b)) {
        curr = (pow2 - cnt) % M;
        if (curr < 0) curr += M;
    } else {
        curr = cnt;
    }
    ans = ans * curr % M;
    }
    cout << ans << endl;
}

