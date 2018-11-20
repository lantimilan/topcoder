// ARRGRAPH.cc
// Correct Answer
// Execution Time: 0.78
#include <iostream>
using namespace std;

// 1. If graph already connected, then done
// 2. If not, then graph cannot have more than one good primes
// [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47]
// good primes are primes such that 2*p >= 50
// proof of 2:
// If the graph has two good primes, e.g. 43, and 47. Then all
// other node, and 47, connect to 43, and all other nodes,
// and 43, connect to 47. Therefore the graph is connected via
// two centers, 43, and 47.
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void dfs(int s, int A[], int N, int visit[]) {
    visit[s] = 1;
    for (int i = 0; i < N; ++i) if (gcd(A[i], A[s]) == 1 && !visit[i]) {
        dfs(i, A, N, visit);
    }
}

bool connected(int A[], int N) {
    int visit[50] = {0};
    dfs(0, A, N, visit);
    for (int i = 0; i < N; ++i) if (!visit[i])
        return false;
    return true;
}

int main () {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        int A[50];
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        if (connected(A, N)) {
            cout << 0 << endl;
            for (int i = 0; i < N; ++i) cout << A[i] << ' ';
            cout << endl;
        } else {
            cout << 1 << endl;
            if (A[0] == 47) A[0] = 43;
            else A[0] = 47;
            for (int i = 0; i < N; ++i) cout << A[i] << ' ';
            cout << endl;
        }
    }
}
