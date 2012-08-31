// =========================================================
// 
//       Filename:  prob2C.cpp
// 
//    Description:  C. Commentator problem
// 
//        Version:  1.0
//        Created:  03/24/2011 07:25:34 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/24/2011, LI YAN
// 
// =========================================================

// since all angles are equal, d(x,a), d(x,b), d(x,c) have the same ratio as ra,
// rb, rc. Note ra, rb, and rc are all integers. gcd?
//
// How to find points that has d(x,a)/d(x,b) = 2, for example?
// For (x1,y1,r1) and (x2,y2,r2), the trajectary is a circle!
//
// Note the use of #ifdef to selectively compile test code and real code
//#define TEST
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

const double EPS=1.0e-6;
const double INF=1.0e+6;

bool iszero(double d)
{ return fabs(d)<EPS; }

struct Point {
    double x,y;
    Point() { x=y=0.0; }
    Point(double xx, double yy) { x=xx; y=yy; }
};

Point operator*(double s, Point p) { return Point(s*p.x, s*p.y); }
Point operator/(Point p, double s) { assert(!iszero(s)); return Point(p.x/s, p.y/s); }
ostream& operator<<(ostream& os, Point p) { return os << "(" << p.x << "," << p.y << ")"; }

Point operator+(Point p1, Point p2)
{ return Point(p1.x+p2.x, p1.y+p2.y); }

Point operator-(Point p1, Point p2)
{ return Point(p1.x-p2.x, p1.y-p2.y); }

bool operator==(Point p1, Point p2)
{ return iszero(p1.x-p2.x) && iszero(p1.y-p2.y); }

double cross(Point p1, Point p2)
{
    return p1.x*p2.y-p1.y*p2.x;
}

Point rotate(Point p, double theta)
{
    double x = p.x*cos(theta)-p.y*sin(theta);
    double y = p.y*cos(theta)+p.x*sin(theta);
    return Point(x,y);
}

double sqr(double x) { return x*x; }
double dist2(Point p1, Point p2) { return sqr(p1.x-p2.x)+sqr(p1.y-p2.y); }
double dist(Point p1, Point p2) { return sqrt(dist2(p1,p2)); }

struct Circle {
    Point ctr; 
    double r;
    Circle() : ctr(),r(0.0) {}
    Circle(Point pt, double rr) : ctr(pt),r(rr) {}
};

void pt2line(Point p1, Point p2, double &A, double &B, double &C)
{
    double x1=p1.x, y1=p1.y, x2=p2.x, y2=p2.y;
    A = y2-y1; B = x1-x2; C = A*x1+B*y1;
}


Point lineinter(double A1, double B1, double C1, double A2, double B2, double C2)
{
	//cout << A1 << " " << B1 << " " << C1 << endl;
	//cout << A2 << " " << B2 << " " << C2 << endl;
    double d = cross(Point(A1,A2),Point(B1,B2)); //cout << d << endl;
    if (iszero(d)) { assert(false); } // should never happen
    double a1 = B2/d, b1 = -B1/d, a2 = -A2/d, b2 = A1/d;
    double x = a1*C1 + b1*C2;
    double y = a2*C1 + b2*C2;
		//cout << x << " " << y << endl;
    return Point(x,y);
}

double ptLineDist(Point pt, Point p1, Point p2)
{
    Point v1 = p1-pt, v2=p2-pt;
    double area = cross(v1,v2);
    return fabs(area)/dist(p1,p2);
}

Point line(Circle cir[])
{
    assert(cir[0].r==cir[1].r && cir[1].r==cir[2].r);
    double A1,B1,C1, A2,B2,C2;
    double D1,E1,F1, D2,E2,F2;
    pt2line(cir[0].ctr, cir[1].ctr, A1,B1,C1);
    D1=-B1; E1=A1; 
    Point mid=(cir[0].ctr+cir[1].ctr)/2.0;
    F1=D1*mid.x+E1*mid.y;
    pt2line(cir[1].ctr, cir[2].ctr, A2,B2,C2);
    D2=-B2; E2=A2;
    mid=(cir[1].ctr+cir[2].ctr)/2.0;
    F2=D2*mid.x+E2*mid.y;
    //cout << D1 << " " << E1 << " " << F1 << endl;
    //cout << D2 << " " << E2 << " " << F2 << endl;
    return lineinter(D1,E1,F1,D2,E2,F2);
}

// uses the fact that the trajectary of point is 
// a circle and the center of that circle, as well
// as the near and far points are on line (p1,p2)
Circle getcircle(Circle c1, Circle c2)
{
  	double r1 = c1.r, r2=c2.r;
  	Point p1=c1.ctr, p2=c2.ctr;
		Point p12 = p1-p2;
		Point q1 = r2/(r1+r2)*p12 + p2;
		Point q2 = r2/(r2-r1)*p12 + p2;
		Point ctr = (q1+q2)/2.0;
		double len = dist(q1,q2)/2.0;
    return Circle(ctr,len);
}

// one line, one circle
// may have one of two intersections
// return intersection closest to midpoint
Point linecircle(Circle cir[])
{
    assert(cir[0].r == cir[1].r);
    Circle cc = getcircle(cir[1], cir[2]);

    double A1,B1,C1, A2,B2,C2;
    Point p1=cir[0].ctr, p2=cir[1].ctr, p12=(p1+p2)/2.0;
    pt2line(p1,p2,A1,B1,C1);
    A2=-B1,B2=A1,C2=A2*p12.x+B2*p12.y;
    C1=A1*cc.ctr.x+B1*cc.ctr.y;
    Point mid = lineinter(A1,B1,C1,A2,B2,C2);
		Point diff = p12-mid;

    double d2line = ptLineDist(cc.ctr, p12, mid);
    if (d2line-cc.r>EPS) return Point(INF,INF);
		double chord = sqrt(sqr(cc.r)-sqr(d2line));
		diff = (chord/dist(mid,p12))*diff;
		Point q1, q2;
		q1 = mid + diff; q2 = 2*mid - q1;
    if (dist2(q1,p1) <= dist2(q2,p1)) return q1;
    else return q2;
}

// could have one, or two intersections
// or the two circles may coincide
// the case that two circles coincide cannot happen, here is why
// the nearest point to a vertex is on the line connecting the center of circle
// to that vertex, and if a point on the circle is nearest to one vertex, it
// must be also nearest to the other two vertices. This implies that all three
// vertices collinear, which is impossible since the problem statement says they
// are not collinear.
Point twocircles(Circle cir[])
{
    Circle cc1, cc2;
    cc1 = getcircle(cir[0], cir[1]);
    cc2 = getcircle(cir[1], cir[2]);
    double r1 = cc1.r, r2 = cc2.r;
    double dd = dist(cc1.ctr, cc2.ctr); assert(!iszero(dd));
    cout << cc1.ctr << " " << r1 << "\t" << cc2.ctr << " " << r2 << endl;
    if (dd-(r1+r2)>EPS) return Point(INF,INF);
    cout << dd << endl;
 
    double cost = fabs((sqr(r1)+sqr(dd)-sqr(r2))/(2*r1*dd));
    double ang = acos(cost); cout << "theta " << cost << " " << ang << endl;
    Point mid = (r1*cost/dd)*(cc2.ctr-cc1.ctr);
    Point q1 = 1.0/cost*rotate(mid, ang)+cc1.ctr;
    Point q2 = 1.0/cost*rotate(mid,-ang)+cc1.ctr;
    if (dist2(q1,cir[0].ctr) <= dist2(q2,cir[0].ctr)) return q1;
    else return q2;
}

#ifdef TEST 
void solve(Circle cir[])
#else
void solve()
#endif
{
    Point res;
    #ifndef TEST
    Circle cir[3];
    for(int i=0; i<3; ++i) cin >> cir[i].ctr.x >> cir[i].ctr.y >> cir[i].r;
    #endif
    if (cir[0].r == cir[1].r && cir[1].r == cir[2].r) res=line(cir);
    else if ((cir[0].r!=cir[1].r) && (cir[1].r!=cir[2].r) && (cir[2].r!=cir[0].r)) 
        res=twocircles(cir);
    else
    {
        if (cir[0].r==cir[1].r) res=linecircle(cir);
        else { assert(cir[1].r==cir[2].r);
            swap(cir[0],cir[2]);
            res=linecircle(cir);
        }
    }
    if (res.x != INF) cout << fixed << setprecision(5) << res.x << " " << res.y << endl;
    if (res.x != INF)
    {
    double d[3];
    for(int i=0; i<3; ++i) d[i] = dist(cir[i].ctr,res);
    cout << "dist to point " << d[0] << " " << d[1] << " " << d[2] << endl;
    if (!iszero(d[0]*cir[1].r-d[1]*cir[0].r) || !iszero(d[1]*cir[2].r-d[2]*cir[1].r))
    { cerr << "test failed\n" << cir[0].ctr << " " << cir[0].r << '\n'
        << cir[1].ctr << " " << cir[1].r << '\n'
        << cir[2].ctr << " " << cir[2].r << '\n'
        << res << '\n'; }
    }
}
int main()
{
    #ifndef TEST
    solve();
    #else
    srand((unsigned)time(NULL));
    for(int i=0; i < 10; ++i)
    {
        Circle cir[3];
        for(int k=0; k<3; ++k)
        {
            cir[k].ctr.x = int(rand()/(double)RAND_MAX * 1000);
            cir[k].ctr.y = int(rand()/(double)RAND_MAX * 1000);
            cir[k].r = int(rand()/(double)RAND_MAX * 1000);
        }
        bool good = true;
        for(int k1=0; k1<3; k1++)
        for(int k2=0; k2<3; k2++) if (k1!=k2)
        {
            double d = dist(cir[k1].ctr, cir[k2].ctr);
            double r1 = cir[k1].r, r2 = cir[k2].r;
            if (r1+r2 >= d) { good = false; goto done; }
        }
        done:
        if (good) solve(cir);
        else --i;
    }
    #endif
}

/* ***********************
 * simplified getCircle() implementation
 * improved somehow, some assertion fired
 * 360633 Mar 28, 2011 4:31:30 AM lantimilan 2C - Commentator problem GNU C++ Runtime error on test 12 30 ms 1400 KB 
 *
 * fixed issue in getcircle()
 * 354354        Mar 26, 2011 2:50:42 AM    lantimilan        2C - Commentator
 * problem       GNU C++     Wrong answer on test 2      10 ms       1400 KB
 *
 *
 * fixed output to 5 digits after decimal point
 * 354353        Mar 26, 2011 2:41:46 AM    lantimilan        2C - Commentator
 * problem       GNU C++     Wrong answer on test 2      10 ms       1400 KB 
 *
 * first submission
 * 354332        Mar 26, 2011 1:41:58 AM    lantimilan        2C - Commentator
 * problem       GNU C++     Wrong answer on test 2      10 ms       1400 KB 
 * */
