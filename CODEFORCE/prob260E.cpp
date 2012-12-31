// try all 9! permutations if we label from top down and left to right
// for each perm, try to find two horizontal lines to get
// a[0] + a[1] + a[2]
// a[3] + a[4] + a[5]
// a[6] + a[7] + a[8]
// and then two vertical lines to get column sums correct
//
// The lines are obtained by binary search
// since x[i], y[i] are integers, we only need split lines to be in
// integer or .5 places
//
// time: 9! * log(10^9) = 10^6 * 30 = 10^7
//
// Question: if row[3] and col[3] are good, does that imply all a[0..8] are good?
/////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
using namespace std;

const int M = 1e5;
int X[M+5];
int Y[M+5];
int a[10];

int bsearch(int lo, int hi, int target)
{
}

int main()
{
    int n; cin >> n;
    int xmin, xmax, ymin, ymax;
    for (int i=0; i<n; ++i) { cin >> X[i] >> Y[i]; X[i] <<= 1; Y[i] <<= 1; }
    for (int i=0; i<9; ++i) cin >> a[i];

    xmin = xmax = X[0]; ymin = ymax = Y[0];
    for (int i=1; i<n; ++i) {
        xmin = min(xmin, X[i]);
        xmax = max(xmax, X[i]);
        ymin = min(ymin, Y[i]);
        ymax = max(ymax, Y[i]);
    }
    xmin--; xmax++; ymin--; ymax++;

    int perm[9];
    for (int i=0; i<9; ++i) perm[i] = i;
    do {
        int row[3] = {0}, col[3] = {0};
        for (int i=0; i<3; ++i) for (int j=0; j<3; ++j) row[i] += a[perm[i*3+j]];
        for (int i=0; i<3; ++i) for (int j=0; j<3; ++j) col[i] += a[perm[i+j*3]];

    } while (next_permutation(perm, perm+9));
}
