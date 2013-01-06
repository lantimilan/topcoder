#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int y1, y2, yw, xb, yb, r;
    cin >> y1 >> y2 >> yw >> xb >> yb >> r;

    const double EPS=1.0e-8;

    double lo=0, hi=xb-EPS;
    double ans = -1;
    for (int i=0; i<1000; ++i) {
        double xw = (lo+hi)/2;
        double yg;
        yg = yw - xw*(yw-yb)/(xb-xw);
        if (r<xw-EPS && y1 <= yg-r-EPS && yg+r+EPS <= y2) { ans = xw; break; }
        if (y1 > yg-r-EPS) lo = xw;
        else hi = xw;
    }

    if (ans < 0) puts("-1");
    else printf("%.10lf\n", ans);
}
