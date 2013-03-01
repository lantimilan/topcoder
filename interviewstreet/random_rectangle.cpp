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
double dp[55][105][55][55];  // index, sum, last, nelems

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

int genpart(int val, int start, vector<int> &pre, const vector<int> &avail, double &pr)
{
    if (val < 0) return 0;
    if (val == 0) {
        // process pre as a partition
        //for (int i=0; i<pre.size(); ++i) cout << pre[i] << ' '; cout << endl;
        /*
        int vcnt[55] = {0}, pcnt[55] = {0};
        for (int i=0; i<pre.size(); ++i) pcnt[pre[i]]++;
        for (int i=0; i<avail.size(); ++i) if (avail[i] > 0) vcnt[avail[i]]++;

        bool good = true;
        for (int v=1; v<=R; ++v) if (pcnt[v] > vcnt[v]) good =false;

        if (good) {
            double cur = 1;
            for (int v=1; v<=R; ++v) cur *= comb[vcnt[v]][pcnt[v]];
            int n = avail.size();
            cur /= (n * comb[n-1][pre.size()]);
            pr += cur;
        }
        */
        return 1;
    }
    int ans = 0;
    for (int i = start; i <= val; ++i) {
        pre.push_back(i);
        ans += genpart(val-i, i, pre, avail, pr);
        pre.pop_back();
    }
    return ans;
}

double calc(int height, vector<int> vec)
{
    double ans = 0;
    for (int i = 0; i < vec.size(); ++i) if (vec[i] + height > R) {
        int old = vec[i]; vec[i] = -1;
        // solve for height and vec
        vector<int> tmp;
        double pr = 0;
        genpart(height, 1, tmp, vec, pr);
        ans += pr;
        vec[i] = old;
    }
    //cout << "calc " << height << ' ' << vec[vec.size()-1] << ' ' << ans << endl;
    return ans;
}

int main()
{
/*  test partition  */
    /* only .245 sec
    for (int i=1; i<=50; ++i) {
        cout << "i = " << i << endl;
        vector<int> v;
        int cnt = genpart(i, 1, v);
        cout << "part = " << cnt << endl << endl;
    }
    return 0;
    */

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
        /*
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
        */

        // generate all partition of v = 1 to 50
        vector<int> vec;
        for (int i=s; i<n; ++i) vec.push_back(size[i]);
        int nvec = vec.size();

        memset(prob, 0, sizeof prob);
        int total = 0;
        for (int i = 0; i < nvec; ++i) total += vec[i];

        if (total <= R) prob[total] = 1;
        else {
            for (int height = 1; height <= R; ++height) {
            cout << "s " << s << " height " << height << endl;
                prob[height] = calc(height, vec);
            }
        }

        for (int width = 1; width <= R; ++width)
        for (int height = 1; height <= R; ++height) {
            double p1, p2;
            p1 = widpr[width][s]; //p2 = heipr[height] / fact[n-s];
            p2 = prob[height]; //if (p2 > 0) cout << "s " << s << ", " << height << ' ' << p2 << endl;
            ans += width * height * p1 * p2 * split;
            //cout << s << ' ' << width << ' ' << height << ' ' << p1 << ' ' << p2 << endl;
        }
    }
    cout << fixed << setprecision(6) << ans << endl;
}

// 2^n, still TLE but better than fact(n)
