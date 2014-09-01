// prob451B.cpp
// compare to a sorted array to determine start and end

#include <algorithm>
#include <iostream>
using namespace std;

int a[100000+5];
int b[100000+5];  // sorted

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        a[i] = b[i] = k;
    }

    sort(b, b + n);
    int begin, end; begin = end = -1;
    for (begin = 0; begin < n; ++begin) {
        if (a[begin] != b[begin]) break;
    }
    for (end = n-1; end >= 0; --end) {
        if (a[end] != b[end]) break;
    }
    bool can;
    if (begin > end) {
        begin = end = 0;
        can = true;
    } else {
        can = true;
        reverse(a + begin, a + end + 1);
        for (int i = 0; i < n; ++i) {
            if (a[i] != b[i]) { can = false; break; }
        }
    }
    if (can) {
        cout << "yes" << endl;
        cout << begin+1 << ' ' << end + 1 << endl;
    } else {
        cout << "no" << endl;
    }
}
