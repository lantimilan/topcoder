// prob459A.cpp

#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
    int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;

    int x3, y3, x4, y4;
    if (x1 == x2) {
        int s = y2 - y1;
        x3 = x4 = x1 + s;
        y3 = y1; y4 = y2;
    } else if (y1 == y2) {
        int s = x2 - x1;
        y3 = y4 = y1 + s;
        x3 = x1; x4 = x2;
    } else {
        if (abs(y2 - y1) != abs(x2 - x1)) {
            cout << -1 << endl;
            return 0;
        }
        x3 = x1; y3 = y2;
        x4 = x2; y4 = y1;
    }
    cout << x3 << ' ' << y3 << ' ' << x4 << ' ' << y4 << endl;
}
