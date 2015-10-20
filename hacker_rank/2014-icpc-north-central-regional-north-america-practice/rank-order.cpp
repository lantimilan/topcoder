// rank-order.cpp
#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

pair<int,int> posA[1000000+5];
pair<int,int> posB[1000000+5];
int rankA[1000000+5];
int rankB[1000000+5];

void read(pair<int,int> arr[], int N) {
    for (int i = 0; i < N; ++i) {
        cin >> arr[i].first;
        arr[i].second = i;
    }
}

void get_rank(pair<int,int> arr[], int N, int out[]) {
    for (int i = 0; i < N; ++i) {
        int x = arr[i].second;
        out[x] = i;
    }
}

int main() {
    int tcase = 0;
    int N;
    while (cin >> N) {
        read(posA, N);
        read(posB, N);

        sort(posA, posA + N); get_rank(posA, N, rankA);
        sort(posB, posB + N); get_rank(posB, N, rankB);

        int mx = -1;
        for (int i = 0; i < N; ++i) {
            if (rankA[i] != rankB[i]) {
                mx = max(mx, max(rankA[i], rankB[i]));
            }
        }
        cout << "Case " << (++tcase) << ": ";
        if (mx < 0) {
            cout << "agree" << endl;
        } else {
            cout << N - mx << endl;
        }
    }
}
