/* Enter your code here. Read input from STDIN. Print output to STDOUT */
/* Enter your code here. Read input from STDIN. Print output to STDOUT */

// the trajectory of a point with d1/d2 = a for (x1, y1) and (x2, y2) is a circle!
#include <algorithm>
#include <cmath>
#include <iomanip>
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
    t1 = sqr((a2*x2-x1)/(a2-1)) - 1/(a2-1)*(a2*x2*x2-x1*x1);
    t2 = sqr((a2*y2-y1)/(a2-1)) - 1/(a2-1)*(a2*y2*y2-y1*y1);
    radius = sqrt(t1+t2);
    //cout << "radius " << radius << " xc " << xc << " yc " << yc << endl;
}

// http://2000clicks.com/mathhelp/GeometryConicSectionCircleIntersection.aspx
// K = (1/4)sqrt(((rA+rB)2-d2)(d2-(rA-rB)2))
// d2 = (xB-xA)2 + (yB-yA)2 
// x = (1/2)(xB+xA) + (1/2)(xB-xA)(rA2-rB2)/d2 ± 2(yB-yA)K/d2 
// y = (1/2)(yB+yA) + (1/2)(yB-yA)(rA2-rB2)/d2 ± -2(xB-xA)K/d2
// this one has poor precision, instead use (0,0) and (d,0)
// and vector arithmetic with complex number to derive axis rotation and translation
void intersect_circle(double r1, double x1, double y1,
                     double r2, double x2, double y2,
                     double &x3, double &y3,
                     double &x4, double &y4)
{
    //cout << "r1 x1 y1 r2 x2 y2 " 
    //    << r1 << ' ' << x1 << ' ' << y1 << ' '
    //    << r2 << ' ' << x2 << ' ' << y2 << endl;
    double d, d2, u1, w1, u2, w2, xnew, ynew;
    d2 = sqr(x2-x1) + sqr(y2-y1);
    d = sqrt(d2);
    xnew = (r1*r1 - r2*r2 + d2)/(2*d);
    ynew = sqrt(r1*r1 - xnew*xnew);
    //cout << "xnew, ynew " << xnew << ' ' << ynew << endl;
    u2 = x2 - x1; w2 = y2 - y1;
    u1 = 1/d * (u2*xnew - w2*ynew);
    w1 = 1/d * (w2*xnew + u2*ynew);
    x3 = x1 + u1;
    y3 = y1 + w1;
    ynew = -ynew;
    u1 = 1/d * (u2*xnew - w2*ynew);
    w1 = 1/d * (w2*xnew + u2*ynew);
    x4 = x1 + u1;
    y4 = y1 + w1;    
    if (x3 < x4 || x3==x4 && y3 < y4) { x4=x3; y4=y3; }
    //cout << x3 << ' ' << y3 << ' ' << x4 << ' ' << y4 << endl;
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
    get_circle(b, x[2], y[2], x[3], y[3], r2, xc2, yc2);
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
        if (r1 == 0) { x4 = xc1; y4 = yc1; }  // both circles are points and they coincide
        else {
            intersect_circle(r1, xc1, yc1, r2, xc2, yc2, x3, y3, x4, y4);
        }
        cout << fixed << setprecision(2) << x4 << ' ' << y4 << endl;
    } else {
        if (r1 == r2 && xc1 == xc2 && yc1 == yc2) {
            // two circles overlap            
            double xl, yl;
            xl = xc1 - r1;
            yl = yc1;
            cout << fixed << setprecision(2) << xl << ' ' << yl << endl;
        } else {
            if (dist + r2 >= r1) {
                // one or two sol
                double x3, y3, x4, y4;
                intersect_circle(r1, xc1, yc1, r2, xc2, yc2, x3, y3, x4, y4);
                cout << fixed << setprecision(2) << x4 << ' ' << y4 << endl;
            } else {
                cout << nosol << endl;  // no sol
            }
        }
    }
}
// fixed one issue
// still 19/20