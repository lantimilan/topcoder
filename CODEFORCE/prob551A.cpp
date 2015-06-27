// prob551A.cpp
#include <algorithm>
#include <iostream>
using namespace std;

pair<int,int> A[2005];
int pos[2005];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> A[i].first;
        A[i].second = i;
    }
    sort(A, A+n);
    reverse(A, A+n);
    int cnt = 0;
    int x = 0;
    int prev = 2005;
    for (int i = 0; i < n; ++i) {
        int val = A[i].first;
        int elem = A[i].second;
        if (val < prev) {
            x = i + 1;
            prev = val;
        }
        pos[elem] = x;
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << pos[i];
    }
    cout << endl;
}
