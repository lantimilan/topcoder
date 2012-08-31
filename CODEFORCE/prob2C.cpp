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
// For (x1,y1,r1) and (x2,y2,r2), the trajectary is a circle, or a line if
// r1=r2
//
// the official solution is to find the intersection of two circle/line, which
// is quite messy to implement. there are 4 cases, line-line, line-circle,
// circle-line and circle-circle.
//
// Algorithm:
// take a second look at the equations
//
// (x-x0)^2 + (y-y0)^2 = (s*r0)^2
// (x-x1)^2 + (y-y1)^2 = (s*r1)^2
// (x-x2)^2 + (y-y2)^2 = (s*r2)^2
//
// we can find s(theta), and then get x,y
// -2(x0-x2)*x + -2(y0-y2)*y = s^2*(r0^2-r2^2) - (x0^2+y0^2)
// -2(x1-x2)*x + -2(y1-y2)*y = s^2*(r1^2-r2^2) - (x1^2+y1^2)
//
// Comments:
// - we only need theta2, that is s^2
// - s^2 need to be >1
// - there might be two s values, the problem asks for the smaller one
//
#include <cmath>
#include <cstdio>
using namespace std;

const double EPS=1.0e-7;

int main()
{
    double x[3],y[3],r[3];
    for(int i=0; i<3; ++i)
        scanf("%lf %lf %lf", &x[i],&y[i],&r[i]);

    double a[2],b[2],c[2],d[2],det, x1,x2,y1,y2, delta;
    a[0]=-2*(x[0]-x[2]); a[1]=-2*(x[1]-x[2]);
    b[0]=-2*(y[0]-y[2]); b[1]=-2*(y[1]-y[2]);
    c[0]=r[0]*r[0]-r[2]*r[2]; c[1]=r[1]*r[1]-r[2]*r[2];
    d[0]=x[2]*x[2]-x[0]*x[0]+y[2]*y[2]-y[0]*y[0]; 
    d[1]=x[2]*x[2]-x[1]*x[1]+y[2]*y[2]-y[1]*y[1];
    det=a[0]*b[1]-b[0]*a[1]; // det != 0 because three centers non-collinear

    fprintf(stderr,"%lf\n", det);

    x1=(b[1]*c[0]-b[0]*c[1])/det; // matrix inv
    y1=(c[1]*a[0]-c[0]*a[1])/det;
    x2=(b[1]*d[0]-b[0]*d[1])/det;
    y2=(a[0]*d[1]-a[1]*d[0])/det;

    fprintf(stderr,"%lf %lf %lf %lf\n",x1,y1,x2,y2);

    a[0]=x1*x1+y1*y1;
    b[0]=2*x1*(x2-x[0])+2*y1*(y2-y[0])-r[0]*r[0];
    c[0]=(x2-x[0])*(x2-x[0])+(y2-y[0])*(y2-y[0]);
    delta=b[0]*b[0]-4*a[0]*c[0];
    fprintf(stderr,"%lf %lf %lf (%lf)\n", a[0],b[0],c[0],delta);

    double theta2; // theta^2, theta is the scaling factor, theta>1
    if (fabs(a[0])<EPS) {
        if (fabs(b[0])<EPS) {
            if (fabs(c[0])<EPS) theta2=1.0;
            else theta2=-1.0;
        } else { theta2=-c[0]/b[0]; }
    } else {
        if (delta<-EPS) theta2=-1;
        else {
            theta2=(-b[0]-sqrt(fabs(delta)))/(2*a[0]); // prefer smaller theta2
            fprintf(stderr,"%lf\n",theta2);
            if (theta2<1-EPS) {
                theta2=(-b[0]+sqrt(fabs(delta)))/(2*a[0]);
            }
        }
    }
    fprintf(stderr,"%lf\n", theta2);
    if (theta2>1-EPS) {
        double xans=x1*theta2+x2, yans=y1*theta2+y2;
        printf("%.6lf %.6lf\n", xans, yans);
    }
    else {
        //printf("No Solution.\n");
    }
}
