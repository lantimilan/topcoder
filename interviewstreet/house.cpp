/* Enter your code here. Read input from STDIN. Print output to STDOUT */

// the trajectory of a point with d1/d2 = a for (x1, y1) and (x2, y2) is a circle!
#include <cmath>
#include <iostream>
using namespace std;

inline double sqr(double x)
{
    return x*x;
}
void get_circle(double ratio, double x1, double y1, double x2, double y2,
                double &radius, double &xc, double &yc)
{
    double a2 = sqr(ratio);
    xc = (a2*x2 - x1)/(a2-1);
    yc = (a2*y2 - y1)/(a2-1);
    double t1, t2;
    t1 = sqr(a2*x2-x1) - (a2-1)*(a2*x2*x2-x1*x1);
    t2 = sqr(a2*y2-y1) - (a2-1)*(a2*y2*y2-y1*y1);
    radius = sqrt((t1+t2)/sqr(a2-1));
}

// http://2000clicks.com/mathhelp/GeometryConicSectionCircleIntersection.aspx
// K = (1/4)sqrt(((rA+rB)2-d2)(d2-(rA-rB)2))
// d2 = (xB-xA)2 + (yB-yA)2 
// x = (1/2)(xB+xA) + (1/2)(xB-xA)(rA2-rB2)/d2 ± 2(yB-yA)K/d2 
// y = (1/2)(yB+yA) + (1/2)(yB-yA)(rA2-rB2)/d2 ± -2(xB-xA)K/d2                   
void intersect_circle(double r1, double x1, double y1,
                     double r2, double x2, double y2,
                     double &x3, double &y3,
                     double &x4, double &y4)
{
    double K, d2, t1, t2, t3, s1, s2, s3;
    d2 = sqr(x2-x1) + sqr(y2-y1);
    K  = 1.0/4 * sqrt((sqr(r1+r2) - d2)*(d2 - sqr(r1-r2)));
    t1 = 1.0/2*(x1+x2);
    t2 = 1.0/2 * (x2-x1)*(r1*r1-r2*r2)/d2;
    t3 = 2*(y2-y1)*K/d2;
    s1 = 1.0/2*(y1+y2);
    s2 = 1.0/2 * (y2-y1)*(r1*r1-r2*r2)/d2;
    s3 = 2*(x2-x1)*K/d2;
    x3 = t1 + t2 + t3;
    x4 = t1 + t2 - t3;
    y3 = s1 + s2 + s3;
    y4 = s1 + s2 - s3;
}
                  
int main()
{
    double a, b;
    double x[4], y[4];
    cin >> a >> b;
    for (int i=0; i<4; ++i)
        cin >> x[i] >> y[i];
    double xc1, yc1, r1, xc2, yc2, r2;
    get_circle(a, x[0], y[0], x[1], y[1], r1, xc1, yc1);
    get_circle(b, x[2], y[2], x[3], y[3], r2, xc2, yc1);
    if (r1 < r2) {
        swap(r1, r2); swap(xc1, xc2); swap(yc1, yc2);
    }
    // four cases for two circles
    double dist = sqrt(sqr(xc1-xc2) + sqr(yc1-yc2));
    string nosol = "Impossible!";
    if (dist > r1 + r2) { 
        cout << nosol << endl;  // no sol
    } else if (dist == r1 + r2) {
        // one sol
        double x3, y3, x4, y4;
        intersect_circle(r1, xc1, yc1, r2, xc2, yc2, x3, y3, x4, y4);
        cout << x4 << ' ' << y4 << endl;
    } else {
        if (r1 == r2 && xc1 == xc2 && yc1 == yc2) {
            // two circles overlap
            double xl, yl;
            xl = xc1 - r1;
            yl = yc1;
            cout << xl << ' ' << yl << endl;
        } else {
            if (dist + r2 >= r1) {
                // one or two sol
                double x3, y3, x4, y4;
                intersect_circle(r1, xc1, yc1, r2, xc2, yc2, x3, y3, x4, y4);
                cout << x4 << ' ' << y4 << endl;
            } else {
                cout << nosol << endl;  // no sol
            }
        }
    }
}
