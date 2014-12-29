// prob493B.cpp
#include <iostream>
#include <vector>
using namespace std;

int cmp(const vector<int> &first, const vector<int> &second) {
    int n = min(first.size(), second.size());
    for (int i = 0; i < n; ++i) {
        if (first[i] != second[i]) return (first[i] > second[i]) ? 1 : -1;
    }
    return 0;
}

int main()
{
    int n; cin >> n;
    vector<int> first, second;
    long long sum1 = 0, sum2 = 0;
    string ans1 = "first", ans2 = "second";
    int last = 0;
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        if (a > 0) {
            sum1 += a; first.push_back(a); last = 0;
        } else {
            sum2 += -a; second.push_back(-a); last = 1;
        }
    }
    if (sum1 != sum2) {
        if (sum1 > sum2) cout << ans1 << endl;
        else cout << ans2 << endl;
    } else {
        int result = cmp(first, second);
        if (result > 0) {
            cout << ans1 << endl;
        } else if (result < 0) {
            cout << ans2 << endl;
        } else {
            if (last == 0) cout << ans1 << endl;
            else cout << ans2 << endl;
        }
    }
}

