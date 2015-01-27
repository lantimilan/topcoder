// template.cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MM = 50000;
int A[MM+5];
int larger[MM+5];
int smaller[MM+5];
int N;

bool check() {
    for (int i = 0; i < N; ++i) {
        larger[i] = N + N;
        smaller[i] = 0;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = N-1; j > i; --j) {
            if (A[j] > A[i]) {
                if (larger[i] > A[j]) larger[i] = A[j];
            }
            if (A[j] < A[i]) {
                smaller[i] = 1;
            }
        }
    }
    for (int i = 0; i < N; ++i)
    for (int j = i+1; j < N; ++j) if (A[i] > A[j]) {
        if (smaller[j] > 0 && A[i] > larger[j]) {
            return true;
        }
    }
    return false;
}

void solve(int tcase)
{
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    bool found = false;
    if (check()) found = true;
    else {
        reverse(A, A+N);
        if (check()) found = true;
    }
    // output solution
    cout << "Case #" << tcase << ": ";
    // sol here
    cout << (!found ? "yes" : "no");
    cout << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
