// prob590A.cpp
#include <algorithm>
#include <iostream>
using namespace std;
// 00 will stay, so is 11
// the only thing that changes are 01010
// each step the segment shrink by 1 from both ends
int a[500000+5];

int main () {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    int len = 0;
    int begin, end;
    // begin is the first one whose next is diff,
    // end is the first one whose next is equal, or end is at n-1
    for (begin = 0; begin + 1 < n; ) {
        if (a[begin] != a[begin+1]) {
            for (end = begin+1; end+1 < n && a[end] != a[end+1]; ++end)
                ;
            int curr = end -1 - begin;
            for (int i = 0; i < curr / 2; ++i) {
                a[begin+1 + i] = a[begin];
            }
            for (int i = curr/2; i < curr; ++i) {
                a[begin+1 + i] = a[end];
            }
            len = max(len, (curr+1)/2);
            begin = end;
        } else {
            begin++;
        }
    }
    cout << len << endl;
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << endl;
}
