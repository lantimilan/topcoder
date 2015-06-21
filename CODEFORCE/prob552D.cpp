// prob552D.cpp
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> triple;

int x[2005];
int y[2005];
map<triple,set<pii>> lines;

int gcd(int a, int b) {
    // forgot to put return and this is RE
    return b == 0 ? a : gcd(b, a % b);
}

void normalize(int &a, int &b) {  // a >= 0 and b > 0 if a = 0
    if (a < 0) {
        a = -a; b = -b;
    } else if (a == 0) {
        if (b < 0) b = -b;
    }
    int g = gcd(abs(a), abs(b));
    assert(g > 0);
    a /= g; b /= g;
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    for (int i = 0; i < n; ++i)
    for (int j = i+1; j < n; ++j) {
        int a = y[j] - y[i];
        int b = x[i] - x[j];
        normalize(a, b);
        int c = a * x[i] + b * y[i];
        triple t = make_pair(pii(a,b), c);
        lines[t].insert(pii(x[i],y[i]));
        lines[t].insert(pii(x[j],y[j]));
    }
    long long ans = 1LL * n * (n-1) * (n-2) / 6; //cout << ans << endl;
    long long sub = 0;
    //map<triple,int>::iterator it;
    //for (it = lines.begin(); it != lines.end(); ++it) {
    for (auto& kv : lines) {
        int cnt = kv.second.size();
        //int cnt = it->second;
        sub += 1LL * cnt * (cnt-1) * (cnt-2) / 6;
        //cout << "sub " << sub << endl;
    }
    cout << ans - sub << endl;
}
