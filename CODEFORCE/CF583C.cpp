// CF583C.cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<int> a;
int gcd[500 * 500];
map<int,int> checklist;

int calc(int x, int y) {
    if (y == 0) return x;
    return calc(y, x % y);
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n*n; ++i) cin >> gcd[i];

    sort(gcd, gcd + n*n);

    for (int i = n*n-1; i >= 0; --i) {
        int elem = gcd[i];
        if (checklist[elem]) {
            checklist[elem]--;
        } else {
            for (int x : a) {
                int g = calc(elem, x);
                checklist[g]+=2;
            }
            checklist[elem]++;
            a.push_back(elem);
        }
    }
    for (int x : a) {
        cout << x << ' ';
    }
    cout << endl;
}
