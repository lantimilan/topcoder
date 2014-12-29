// prob493C.cpp

#include <algorithm>
#include <iostream>
using namespace std;

const int N = 200000+5;
int first[N], second[N], merged[2*N];

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> first[i];
    int m; cin >> m;
    for (int i = 0; i < m; ++i) cin >> second[i];

    sort(first, first+n);
    sort(second, second+m);

    int cnt = 0;
    for (int i=0, j=0; i < n || j < m; ) {
        if (i >= n) merged[cnt++] = second[j++];
        else if (j >= m) merged[cnt++] = first[i++];
        else if (first[i] < second[j]) merged[cnt++] = first[i++];
        else merged[cnt++] = second[j++];
    }

    int a = 2 * n, b = 3 * m;
    for (int i = 0; i < cnt; ++i) {
        for (int d = -1; d <= 1; ++d) {
            int v = merged[i] + d;
            int p1 = upper_bound(first, first + n, v) - first;
            int p2 = upper_bound(second, second + m, v) - second;
            int s1 = p1 * 2 + (n - p1) * 3;
            int s2 = p2 * 2 + (m - p2) * 3;
            int diff = s1 - s2;
            int best = a - b;
            if (best < diff || (best == diff && a < s1)) {
                a = s1; b = s2;
            }
        }
    }
    cout << a << ':' << b << endl;
}
