// prob551C.cpp
// binary search and greedy on leaving min # of students in each pile
// why greedy is enough? Because we are always in a better configuration.
#include <cstring>
#include <iostream>
using namespace std;

int N, M;
int A[100000+5];
int boxes[100000+5];

bool check(long long cap) {
    memcpy(boxes, A, sizeof A);
    // use student s to remove as many boxes as possible
    // s start at pos = 0, and the first non-empty pile is at pos = first
    int first = 0;
    int last;
    for (last = N-1; last >= 0 && boxes[last] == 0; --last)
        ;
    for (int s = 0; s < M; ++s) {
        long long budget = cap - first;
        for (; first < N; ++first) {
            long long finish = budget - 1;
            if (boxes[first] <= finish) {
                budget -= boxes[first] + 1;
                boxes[first] = 0;
            } else {  // this student is done
                boxes[first] -= finish;
                break;
            }
        }
    }
    return first > last;
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    long long lo = 0, hi = 1e15;
    while (lo + 1 < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid)) { hi = mid; }
        else { lo = mid; }
    }
    cout << hi << endl;
}
