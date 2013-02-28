// random_rectangle.cpp
//
//

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int n;
int R;
int size[60];
double widpr[60][60], heipr[60];
double pow2[60];
double fact[60];
double comb[60][60];
double prob[60];

void init()
{
    pow2[0] = 1.0;
    for (int i=1; i<=50; ++i)
        pow2[i] = pow2[i-1] / 2;
    fact[0] = 1;
    for (int i=1; i<=20; ++i)
        fact[i] = fact[i-1] * i;
    comb[0][0] = 1;
    for (int i=1; i<=50; ++i) {
        comb[i][0] = 1;
        for (int j=1; j<=i; ++j)
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    }
}

int main()
{
    init();
    cin >> n;
    for (int i=0; i<n; ++i) cin >> size[i];
    cin >> R;

    //cout << "s width height p1 p2\n";
    double ans = 0.0;
    double split = 1.0;
    for (int s=1; s<n; ++s) {
        split /= 2;
        widpr[0][0] = 1;
        for (int width = 0; width <= R; ++width) {
            for (int nw = 1; nw <=s; nw++) {
                widpr[width][nw] = widpr[width][nw-1];
                if (width >= size[nw-1])
                    widpr[width][nw] += widpr[width - size[nw-1]][nw-1];
                widpr[width][nw] *= .5;
            }
        }
        /* fact(n) solution
        memset(heipr, 0, sizeof heipr);
        vector<int> vec;
        for (int i=s; i<n; ++i) vec.push_back(i);
        do {
            int val = 0;
            for (int i=0; i<vec.size(); ++i) {
                if (val + size[vec[i]] <= R) val += size[vec[i]];
                else break;
            }
            heipr[val] += 1;
        } while (next_permutation(vec.begin(), vec.end()));
        */

        // try all subset
        // 2^n solution
        memset(prob, 0, sizeof prob);
        int offset = s;
        int r = n - s;
        for (int b = 0; b < (1<<r); ++b) {
            int sum = 0, nbits = 0;
            for (int i = 0; i < r; ++i) nbits += ((b & 1<<i) != 0);
            for (int i = 0; i < r; ++i) if (1<<i & b) {
                sum += size[offset + i];
            }
            if (sum <= R) {
                if (b+1 == (1<<r)) prob[sum] = 1;
                else {
                for (int i = 0; i < r; ++i) if (1<<i & ~b) {
                    int next = size[offset + i];
                    if (sum + next > R) //prob[sum] += fact[nbits]/fact[r];
                        prob[sum] += 1.0 / (comb[r-1][nbits] * r);
                }
                }
                //cout << "offset " << offset << ' '<< sum << ' ' << prob[sum] << endl;
            }
        }

        for (int width = 1; width <= R; ++width)
        for (int height = 1; height <= R; ++height) {
            double p1, p2;
            p1 = widpr[width][s]; //p2 = heipr[height] / fact[n-s];
            p2 = prob[height];
            ans += width * height * p1 * p2 * split;
            //cout << s << ' ' << width << ' ' << height << ' ' << p1 << ' ' << p2 << endl;
        }
    }
    cout << fixed << setprecision(6) << ans << endl;
}

// 2^n, still TLE but better than fact(n)
