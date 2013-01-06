#include <iostream>
using namespace std;

int main()
{
    int asum, bsum, aa, bb, n;

    asum = bsum = 0;
    aa = bb = 0;

    cin >> n;
    for (int i=0; i<n; ++i) {
        int id, x, y;
        cin >> id >> x >> y;
        if (id == 1) { asum += x; aa += y; }
        else { bsum += x; bb += y; }
    }

    const char *good = "LIVE";
    const char *bad  = "DEAD";
    cout << (asum >= aa ? good : bad) << endl;
    cout << (bsum >= bb ? good : bad) << endl;
}
