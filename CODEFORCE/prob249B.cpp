// binary search for k
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

string line;
int house[500000+5];  // house[i] = 1 means served

int main()
{
    int n, t; cin >> n >> t;
    cin >> line;
    line = "." + line;
    n = line.length();

    int i, j;
    int nhouse=0;
    for (i=0; i<n; ++i) if (line[i] == 'H') nhouse++;
    int lo=-1, hi=n+1;  // lo is infeasible and hi is feasible
    while (lo+1 < hi) {
        // in one trip, go right to collect enough candies
        // then go left to serve all remaining houses
        //
        int k = (lo+hi)/2;
        int serve = nhouse;
        int candy = k;
        int tick=0;
        int pos, last, next;  // last is house served, pos is shop used
        last = pos = next = 0;
        while (serve > 0) {
            // candy >= 0 to begin
            // end at the first candy < 0 or serve = 0
            assert(candy >= 0);
            last = pos;
            for (pos = next+1; pos < n; ++pos) {
                if (line[pos] == 'S') candy++;
                else if (line[pos] == 'H') {
                    if (candy-- > 0) { serve--; }
                }
                if (serve == 0) break;
                if (candy < 0) break;
            }
            tick += pos - last;
            if (serve == 0) break;
            // pos at the first H that needs candy
            assert(candy == -1 && line[pos] == 'H');
            // find next shop to serve pos
            candy++;
            for (next = pos; next < n; ++next) {
                if (line[next] == 'H') { candy--; serve--; }
                else if (line[next] == 'S') candy++;

                if (candy >= 0) break;
            }
            if (candy < 0) break;
            assert(candy == 0);
            tick += 2*(next - pos);
        }
        if (candy < 0 || tick > t) lo = k;
        else hi = k;
    }
    if (hi < n+1) cout << hi << endl;
    else cout << -1 << endl;
}

// to be checked
