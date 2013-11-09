// prob356C.cpp
//
// only get -1 for students = 1, 2, 5
// Proof:
// n = 3k, done
// n = 3k+1, only 1 is a problem, others can be 4 + 3(k-1)
// n = 3k+2, only 2 and 5 is a problem, others can be 4 + 4 + 3(k-2)
//
// if we have 2, 2, then we have to merge into 4
// if we have 4 and 2, then the best is 3 and 3

#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

const int MAX = 1000000+5;
int compartments[MAX];
int prefix[MAX];
int sum;
int N;

int main()
{
    cin >> N;
    sum = 0;
    for (int i = 0; i < N; ++i) {
        int d; cin >> d;
        compartments[i] = d;
        sum += d;
    }
    sort(compartments, compartments + N, greater<int>());

    // prefix[i] = sum(c[0..i))
    prefix[0] = 0;
    for (int i = 0; i < N; ++i) {
        prefix[i+1] = prefix[i] + compartments[i];
    }

    int nfour, nthree;
    nfour = nthree = 0;
    for (int i = 0; i < N; ++i) {
        if (compartments[i] == 4) nfour++;
        if (compartments[i] == 3) nthree++;
    }

    int best = sum+1;
    for (int three = 0; three <= sum / 3; ++three) {
        int four = (sum - 3 * three) / 4;
        int rem = sum - three * 3 - four * 4;
        if (rem != 0) continue;
        int cost = sum - (prefix[three + four]);
        // important, if you do not use all 4's
        // you have to pay 1 for each unused 4 to make it 3
        if (four < nfour) cost += nfour - four;
        best = min(best, cost);
    }

    if (best > sum) best = -1;
    cout << best << endl;
}

// Accepted
