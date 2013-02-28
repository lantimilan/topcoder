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
map<pair<int, long long>, double> prob;

void init()
{
    pow2[0] = 1.0;
    for (int i=1; i<=50; ++i)
        pow2[i] = pow2[i-1] / 2;
    fact[0] = 1;
    for (int i=1; i<=20; ++i)
        fact[i] = fact[i-1] * i;
}

double calc(int val, long long mask)
{
    double ans = 0;
    if (val == 0) return 1;
    if (mask == 0) return 0;
    if (prob.count(make_pair(val, mask))) {
        return prob[make_pair(val, mask)];
    }
    int nbits = 0;
    for (int i=0; i<n; ++i) if (1LL<<i & mask) nbits++;

    for (int i=0; i<n; ++i) {
        if (1LL<<i & mask) {
            if (val >= size[i]) {
                ans += calc(val - size[i], mask & ~(1LL<<i));
            }
        }
    }
    return prob[make_pair(val, mask)] = ans/nbits;
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
        /*
        prob.clear();
        for (int height = 1; height <= R; ++height) {
            long long mask = ((1LL<<n) - 1) & ~((1LL<<s) - 1);
            heipr[height] = calc(height, mask);
        }
        */
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

        for (int width = 1; width <= R; ++width)
        for (int height = 1; height <= R; ++height) {
            double p1, p2;
            p1 = widpr[width][s]; p2 = heipr[height] / fact[n-s];
            ans += width * height * p1 * p2 * split;
            //cout << s << ' ' << width << ' ' << height << ' ' << p1 << ' ' << p2 << endl;
        }
    }
    cout << fixed << setprecision(6) << ans << endl;
}
