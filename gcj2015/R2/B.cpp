// B.cpp
// binary search, failed small and segment fault on large
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef pair<double, double> pdd;

const double EPS = 1e-9;
double V, X;

bool check(deque<pdd> water) {
    double totalvolume = 0.0;
    double avgtemp = 0.0;
    int n = water.size();
    deque<pdd>::const_iterator it;
    for (it = water.begin(); it != water.end(); ++it) {
        double temp = it->first;
        double volume = it->second;
        totalvolume += volume;
        avgtemp += volume * temp;
    }

    if (totalvolume < V - EPS) return false;

    avgtemp /= totalvolume;
    while (totalvolume > V + EPS) {
        if (avgtemp > X) {
            double maxtemp = water.back().first;
            double lastvolume = water.back().second;
            double othervolume = totalvolume - lastvolume;
            double othersum = avgtemp * totalvolume - maxtemp * lastvolume;
            if (othervolume < V) {  // shrink max temp water to fit V
                avgtemp = othersum + maxtemp * (V - othervolume);
                avgtemp /= V;
                totalvolume = V;
            } else {
                avgtemp = othersum / othervolume;
                totalvolume = othervolume;
                water.pop_back();
            }
            if (avgtemp < X + EPS) return true;
        } else {
            double mintemp = water.front().first;
            double firstvolume = water.front().second;
            double othervolume = totalvolume - firstvolume;
            double othersum = avgtemp * totalvolume - mintemp * firstvolume;
            if (othervolume < V) {
                avgtemp = othersum + mintemp * (V - othervolume);
                avgtemp /= V;
                totalvolume = V;
            } else {
                avgtemp = othersum / othervolume;
                totalvolume = othervolume;
                water.pop_front();
            }
            if (avgtemp > X - EPS) return true;
        }
    }
    return fabs(avgtemp - X) <= EPS;
}

void solve(int tcase) {
    // sort input by temp
    int N; cin >> N;
    cin >> V >> X;
    vector<pdd> sources;
    for (int i = 0; i < N; ++i) {
        double rr, tt; cin >> rr >> tt;
        sources.push_back(make_pair(tt, rr));
    }
    sort(sources.begin(), sources.end());

    const double INF = 1e8 + 10;
    double lo = 0, hi = 1e8 + 10;
    for (int i = 0; i < 1000; ++i) {
        double mid = (lo + hi) / 2;
        deque<pdd> water;
        for (int x = 0; x < N; ++x) {
            double temp = sources[x].first;
            double rate = sources[x].second;
            double volume = rate * mid;
            water.push_back(make_pair(temp, volume));
        }
        if (check(water)) hi = mid;
        else lo = mid;
    }
    double ans = (lo + hi) / 2;
    cout << "Case #" << tcase << ": ";
    if (ans > INF - 1) {
        cout << "IMPOSSIBLE";
    } else {
        cout << fixed << setprecision(9) << ans;
    }
    cout << endl;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
