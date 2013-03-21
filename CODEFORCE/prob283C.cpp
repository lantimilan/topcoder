// prob283C.cpp

// each b[i] and c[i] are distinct
// then the edges form disjoint paths and cycles
//
// a sequence of a[1] < a[2] < ... < a[k]
// has one to one mapping with a sequence
// a[1] + 0, a[1] + b[1], a[1] + b[1] + b[2], ...
// where b[i] >= 1
// so a[1] and b[i]'s uniquely define a[1] ... a[k]


#include <iostream>
#include <utility>
using namespace std;

const int MOD = (int)(1e9+7);
int a[305], val[305];
//int cnt[305][100000+5];
int cnt[100000+5];
int nextnode[305];
int len[305];
pair<int,int> edges[305];
int Nedge;

int main()
{
    int n, q, t;
    cin >> n >> q >> t;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < q; ++i) {
        int b, c; cin >> b >> c;
        --b; --c;
        edges[Nedge++] = make_pair(b, c);
    }

    for (int i = 0; i < n; ++i) { nextnode[i] = i; }
    bool update = true;
    bool hascycle = false;
    while (update) {
        update = false;
        for (int i = 0; i < Nedge; ++i) {
            int b, c; b = edges[i].first; c = edges[i].second;
            // c < b
            nextnode[c] = b;
            if (len[b] < len[c] + 1) {
                update = true;
                len[b] = len[c] + 1;
                if (len[b] >= n) { hascycle = true; break; }
            }
        }
        if (hascycle) {
            cout << 0 << endl;
            return 0;  // done with cycle
        }
    }
    for (int i = 0; i < n; ++i) {
        int k = i;
        while (k != nextnode[k]) {
            val[i] += a[k];
            k = nextnode[k];
        }
        val[i] += a[k];
    }

    for (int i = 0; i < n; ++i) {  // subtract all val that must be one or more
        if (len[i] > 0) t -= val[i];  // integer overflow here as val[i] can be 300*10^5
        if (t < 0) break;
    }

    if (t < 0) { cout << 0 << endl; return 0; }

    //cnt[0][0] = 1;
    cnt[0] = 1;
    for (int x = 1; x <= n; ++x)
    {
        for (int v = 0; v <= t; ++v)
        {
            int prev = v - val[x-1];
            //cnt[x][v] = cnt[x-1][v];
            if (prev >= 0) {
                //cnt[x][v] += cnt[x][prev];
                //if (cnt[x][v] >= MOD) cnt[x][v] -= MOD;
                cnt[v] += cnt[prev];
                if (cnt[v] >= MOD) cnt[v] -= MOD;
            }
        }
        //cout << x << ": ";
        //for (int v = 0; v <= t; ++v)
        //    if (cnt[x][v] != 0) cout << " v " << v << " " << cnt[x][v] << "\t";
        //cout << endl;
    }
    //cout << cnt[n][t] << endl;
    cout << cnt[t] << endl;
}

// Accepted
