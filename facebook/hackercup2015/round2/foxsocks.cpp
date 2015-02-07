// foxsocks.cpp
#include <cassert>
#include <iostream>
using namespace std;

const int MM = 1e9;
int S[1000000+5];
int O[1000000+5];
int A[1000000+5];
int B[1000000+5];
int C[1000000+5];
int D[1000000+5];

void gen(int arr[], int n, int mod, int extra, int x, int y, int z) {
    for (int i = 2; i < n; ++i) {
        arr[i] = (1LL * x * arr[i-2] + 1LL * y * arr[i-1] + z) % mod + extra;
    }
}

void update(int& val) {
    if (val >= MM) val -= MM;
}

void solve(int tcase) {
    // N bins, M operations
    int N, M; cin >> N >> M;
    int XS, YS, ZS;
    int XO, YO, ZO;
    int XA, YA, ZA;
    int XB, YB, ZB;
    int XC, YC, ZC;
    int XD, YD, ZD;

    cin >> S[0] >> S[1] >> XS >> YS >> ZS; gen(S, N, MM, 0, XS, YS, ZS);
    cin >> O[0] >> O[1] >> XO >> YO >> ZO; gen(O, M, 4, 1, XO, YO, ZO);
    cin >> A[0] >> A[1] >> XA >> YA >> ZA; gen(A, M, N, 1, XA, YA, ZA);
    cin >> B[0] >> B[1] >> XB >> YB >> ZB; gen(B, M, N, 1, XB, YB, ZB);
    cin >> C[0] >> C[1] >> XC >> YC >> ZC; gen(C, M, MM, 0, XC, YC, ZC);
    cin >> D[0] >> D[1] >> XD >> YD >> ZD; gen(D, M, MM, 0, XD, YD, ZD);

    // bin is 1-based
    // O[i] == 1
    // for bin = A[i], x=0 to A[i] + B[i] - 1, x = B[i]-1
    // socks[bin] += C[i] + x * D[i]
    // output: sum_{x = 0 to B[i]-1} C[i] + x * D[i]
    //
    // O[i] == 2
    // for bin = A[i] to A[i] + B[i] - 1
    // sum += socks[bin]
    // socks[bin] = C[i]
    // output: sum + C[i] * B[i]
    //
    // O[i] == 3
    // for bin = A[i] to A[i] + B[i] - 1
    // sum += socks[bin]
    // output: sum
    //
    // O[i] == 4
    // for bin = A[i] to A[i] + B[i] - 1
    // oddsum += (socks[bin] is odd)
    // output: oddsum
    //
    // ans = sum of all output MOD MM
    int *socks = S;
    int ans = 0;
    for (int i = 0; i < M; ++i) {
        int op = O[i];
        int sum = 0;
        for (int k = 0; k < B[i]; ++k) {
            int bin = (A[i]-1 + k); if (bin >= N) bin -= N;
            int added = 0;
            switch (op) {
                case 1:
                    added = C[i] + 1LL * k * D[i] % MM; update(added);
                    socks[bin] += added; update(socks[bin]);
                    sum += added; update(sum);
                    break;
                case 2:
                    sum += socks[bin]; update(sum);
                    sum += C[i]; update(sum);
                    socks[bin] = C[i];
                    break;
                case 3:
                    sum += socks[bin]; update(sum);
                    break;
                case 4:
                    sum += (socks[bin] & 1);
                    break;
                default:
                    assert(false);
            }
        }
        ans += sum; update(ans);
    }

    cout << "Case #" << tcase << ": ";
    // output sol here
    cout << ans;
    cout << endl;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
