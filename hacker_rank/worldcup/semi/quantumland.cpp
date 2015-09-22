// quantumland.cpp
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;
// the graph is a collection of cycles, assuming all edges exist.

int neighbor[100000+5];
int prob[100000+5];
int vis[100000+5];
int lead[100000+5];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int w, p; cin >> w >> p;
        neighbor[i] = --w;
        prob[i] = p;
    }

    memset(lead, -1, sizeof lead);

    double ans = 0.0;
    for (int i = 0; i < n; ++i) if (!vis[i]) {
        int s = i;
        int curr = s;
        while (!vis[curr]) {
            vis[curr] = 1; lead[curr] = s;
            curr = neighbor[curr];
        }
        if (lead[curr] != s) continue;
        s = curr;
        double ex = 1.0;
        do {
            ex *= 0.01 * prob[curr];
            curr = neighbor[curr];
        } while (curr != s);
        ans += ex;
    }
    //cout << ans << endl;
    ans = 0.01 * (int)(100 * ans + 0.5);
    cout << fixed << setprecision(2) << ans << endl;
}
