// B.cpp

#include <iostream>
using namespace std;


int prisoners[200000+5];

int main()
{
    int n; cin >> n;
    int thresh; cin >> thresh;
    int count; cin >> count;
    for (int i = 0; i < n; ++i) cin >> prisoners[i];

    int ans = 0;
    int ss, ee;
    for (ss = 0; ss < n; ) {
        while (ss < n && prisoners[ss] > thresh) ++ss;
        if (ss >= n) break;
        for (ee = ss+1; ee < n && prisoners[ee] <= thresh; ++ee)
            ;

        if (ee >= ss + count)
            ans += ee - (ss + count) + 1;
        ss = ee;
    }
    cout << ans << endl;
}
