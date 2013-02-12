// prob269B.cpp
// count inversion and greedy remove the max inversion
// this algorithm fails, but why?
//
// the real solution is longest increasing subsequence

#include <iostream>
using namespace std;

int cnt[5005];  // inversions
int a[5005];

int calc(int n)
{
    for (int i=0; i<n; ++i) {
        cnt[i] = 0;
        for (int j=0; j<n; ++j) if (i!=j) {
            if (j < i && a[j] > a[i]) cnt[i]++;
            if (j > i && a[j] < a[i]) cnt[i]++;
        }
    }

    int ans = 0;
    for (int t=0; t<n; ++t) {
        int pivot = -1;
        for (int x=0; x<n; ++x) if (cnt[x] > 0) {
            if (pivot < 0 || cnt[x] > cnt[pivot]) pivot = x;
        }
        if (pivot < 0) break;
        ans++;
        cnt[pivot] = 0;
        for (int j=0; j<n; ++j) {
            if (j < pivot && a[j] > a[pivot]) cnt[j]--;
            if (j > pivot && a[j] < a[pivot]) cnt[j]--;
        }
    }
    return ans;
}

int main()
{
    int n, m; cin >> n >> m;
    for (int i=0; i<n; ++i) {
        double x;
        cin >> a[i] >> x;
    }
    int ans = calc(n);
    cout << ans << endl;
}
