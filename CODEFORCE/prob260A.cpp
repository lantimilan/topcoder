// first time try 0 to 9
// then use 0

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int a, b, n; cin >> a >> b >> n;
    int i;
    for (i=0; i<10; ++i) {
        if ((a*10 + i) % b == 0) break;
    }
    if (i>=10) cout << -1 << endl;
    else cout << a << i << string(n-1, '0') << endl;
}
