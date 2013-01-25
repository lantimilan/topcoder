// the following is dumb, if there is a point below the line, then it will
// make a better inclination
//
// convex hull,
// only need upper hull as all other points need to be below the line

// lesson:
// int abs(int);
// long labs(long);
// long long llabs(long long);

#include <iostream>
using namespace std;

typedef long long int64;

int main()
{
    int N; cin >> N;
    int64 a, b; cin >> a >> b;
    int x=0;
    int64 m = b-a;
    if (m<0) m = -m;
    for (int i=2; i<N; ++i) {
        a=b; cin >> b;
        int64 v = b-a;
        if (v<0) v = -v;
        if (v>m) { m=v; x=i-1; }
    }
    cout << x+1 << ' ' << x+2 << endl;
}
