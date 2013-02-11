// prob269A.cpp
#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

pii box[100000+5];

int main()
{
    int n; cin >> n;
    for (int i=0; i<n; ++i) cin >> box[i].first >> box[i].second;
    sort(box, box+n);
    for (int i=0; i+1<n; ++i) {
        int next = box[i+1].first;
        int k = box[i].second;
        int base = box[i].first;
        while (k > 0 && base < next) {
            k = (k+3)/4; base++;
        }
        box[i+1].second += max(0, k-box[i+1].second);
    }
    int ans = box[n-1].first;
    int num = box[n-1].second;
    if (num == 1) ans++;
    else {
    while (num > 1) {
        num = (num+3)/4; ans++;
    }
    }
    cout << ans << endl;
}
