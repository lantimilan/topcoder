// shopping.cpp
#include <cassert>
#include <iostream>
#include <iomanip>
using namespace std;

int waiting[3005][1000];
double prob[3005][1000];
double exp_wait[3005];

int encode(int a[], int size) {
    int ans = 0;
    for (int i = 0; i < size; ++i) {
        ans = ans * 10 + a[i];
    }
    return ans;
}

void decode(int val, int a[], int size) {
    for (int i = size-1; i >= 0; --i) {
        a[i] = val % 10;
        val /= 10;
    }
}

int main() {
    int N, M, K; cin >> N >> M >> K;
    int size = K;
    int cap = 1;
    for (int i = 0; i < size; ++i) cap *= 10;

    cout << cap << endl;
    int abc[5]; decode(cap-1, abc, size);
    for (int i = 0; i < size; ++i) {
        cout << abc[i] << ' ';
    }
    cout << endl;

    waiting[0][0] = 0;
    prob[0][0] = 1.0;


    for (int x = 0; x < N; ++x)
    for (int state = 0; state < cap; ++state) {
        int a[5]; decode(state, a, size);
        int minpos = 0;
        int minval = a[0];
        for (int i = 1; i < size; ++i) {
            if (a[i] < minval) {
                minpos = i; minval = a[i];
            }
        }
        int b[5];
        for (int i = 0; i < size; ++i) {
            b[i] = a[i] - minval;
        }
        assert(b[minpos] == 0);
        for (b[minpos] = 1; b[minpos] <= M; ++b[minpos]) {
            int s2 = encode(b, size);
            double p = 1.0/M * prob[x][state];
            prob[x+1][s2] += p;
            waiting[x+1][s2] = (waiting[x][state] + minval) * p;
            cout << x+1 << ' ' << s2 << ' '
                << x << ' ' << state << ' ' << prob[x][state] << ' '
                << prob[x+1][s2] << ' ' << waiting[x+1][s2] << endl;
        }
    }

    for (int i = 1; i <= N; ++i)
    for (int s = 0; s < cap; ++s) {
        exp_wait[i] = waiting[i][s] * prob[i][s];
    }

    for (int i = 1; i <= N; ++i) {
        cout << fixed << setprecision(5) << exp_wait[i] << endl;
    }
}
