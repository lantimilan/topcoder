// ilia.cpp
#include <algorithm>
#include <iostream>
using namespace std;

int A[5005];
int A2[5005];

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        A2[i] = A[i] * A[i];
    }
    long long acute, right, obtuse;
    acute = right = obtuse = 0;
    for (int i = 0; i < N; ++i)
    for (int j = i+1; j < N; ++j) {
        int a = A[i], b = A[j];
        int s = a + b;
        int s2 = a*a + b*b;
        int end = lower_bound(A, A+N, s) - A;
        int begin = j+1;
        int* p1 = lower_bound(A2+begin, A2+end, s2);
        int* p2 = upper_bound(A2+begin, A2+end, s2);
        acute += p1 - (A2 + begin);
        right += p2 - p1;
        obtuse += A2+end - p2;
    }
    cout << acute << ' ' << right << ' ' << obtuse << endl;
}
