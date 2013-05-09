// probA.cpp

// if n is even and minus is odd,
// then any operations will leave minus odd
// so we have one item cannot be collected

// if n is odd and minus is odd,
// after one operation we have n odd and minus even
// then we can use (n-1) plus and one minus to make all minus to plus

// if n is odd and minus is even
// 1. if minus < n, then use (n-1) plus and one minus to make all minus to plus
// 2. minus >= n, flip minus so that minus < n, and minus is odd now
// do one more operation with a plus and b minus with b = minus odd
// then a = n - minus is even, and a < n
// so new minus = a and we know have 0 < minus < n and is even

// if n is even and minus is even
// flip minus so that minus <= n
// then use (n-1) plus and one minus to make all minus plus

// to summarize, as long as minus is even, we can use (n-1) plus and one minus
// to make all minus to be plus. If minus is odd, if n is also odd, we can use n
// to turn minus into even. If n is even, then there is no way to turn minus into odd,
// so we have to give up one item.

#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    int a[500];
    int minus = 0;
    int sum = 0;
    for (int i = 0; i < 2*n-1; ++i) {
        cin >> a[i];
        if (a[i] < 0) {
            minus++; a[i] = -a[i];
        }
        sum += a[i];
    }
    sort(a, a+2*n-1);
    if (n % 2 == 0 && minus % 2 == 1) {
        sum -= 2*a[0];
    }
    cout << sum << endl;
}
