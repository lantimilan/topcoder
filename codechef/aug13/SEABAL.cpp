// SEABAL.cpp

// maintain two vectors, sorted <l[i], r[i]>
// a vector of consecutive zeroes

#include <cassert>
#include <cstdio>
#include <set>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

multiset<pii> segs;
set<int> start, end;

int n, m, k;
int a[100000+5];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d", a+i);
    for (int i = 0; i < m; ++i) {
        int l, r; scanf("%d%d", &l, &r);
        segs.insert(pii(l-1, r));
    }

    scanf("%d", &k);
    int pos, ans = 0;
    for (int i = 0; i < k; ++i) {
        int idx; scanf("%d", &idx);
        pos = ans + idx - 1;
        // got RE, so one of the two assertion is incorrect
        assert(0 <= pos && pos < n);
        assert(a[pos] > 0);
        a[pos]--;
        printf("pos %d a[%d] = %d\n", pos, pos, a[pos]);
        if (a[pos] == 0) {
            // update zeroes
            int ss, tt, s2, t2;
            ss = pos; tt = pos+1;
            if (end.count(ss)) { s2 = *--start.lower_bound(ss); end.erase(ss); }
            else { s2 = ss; start.insert(ss); }

            if (start.count(tt)) { t2 = *end.lower_bound(tt); start.erase(tt); }
            else { t2 = tt; end.insert(tt); }

            printf("ss %d tt %d s2 %d t2 %d\n", ss, tt, s2, t2);
            // use [s2, t2) to capture some segs
            bool update = true;
            while (update) {
                update = false;
                multiset<pii>::iterator it = segs.lower_bound(pii(s2, 0));  // this is wrong (3,6) (4,5) then (3,5) is able to cover (4,5) but not (3,6)
                if (it == segs.end()) break;
                printf("it %d %d\n", it->first, it->second);
                if (s2 <= it->first && it->second <= t2) {
                    ans += segs.count(*it);
                    segs.erase(*it);
                    //segs.erase(it); ans++;
                    update = true;
                }
            }
        }
        printf("%d\n", ans);
    }
}

// WA, what did I miss?
