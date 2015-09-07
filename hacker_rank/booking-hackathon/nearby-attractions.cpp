// nearby-attractions.cpp
// Failed Testcase 4
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int id[205];
double lat[205], lon[205];

double calc_move(string transport, double minutes) {
    double speed;
    if (transport == "metro") {  // 20km/h
        speed = 20.0;
    } else if (transport == "foot") {  // 5km/h
        speed = 5.0;
    } else if (transport == "bike") {  // 15km/h
        speed = 15.0;
    } else {
        assert(false);
    }
    return speed * minutes / 60.0;
}

double deg2rad(double deg) {
    const double PI = 3.14159265359;
    return PI * deg / 180;
}

double calc_dist(double lat1, double lon1, double lat2, double lon2) {
    const double EARTH_RADIUS = 6371;  //in km
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);

    double dist = acos(
        sin(lat1) * sin(lat2) +
        cos(lat1) * cos(lat2) * cos(lon2 - lon1) ) * EARTH_RADIUS;

    /*
    cout << fixed << setprecision(10) << "calc_dist: "
        << lat1 << ' ' << lon1 << ' ' << lat2 << ' ' << lon2 << ' '
        << dist << endl;
    */
    return dist;
}

double parse(string s) {
    double d = 0;
    for (int i = 0; i < s.length(); ++i) if (s[i] != '.') {
        d = d * 10 + s[i] - '0';
    }
    d = d / 1000000.0;
    //cout << s << ' ' << fixed << setprecision(10) << d << endl;
    return d;
}

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        string s1, s2;
        cin >> id[i] >> s1 >> s2;
        lat[i] = parse(s1);
        lon[i] = parse(s2);
        //cout << id[i] << ' ' << lat[i] << ' ' << lon[i] << endl;
    }

    int M; cin >> M;
    while (M--) {
        string s1, s2; cin >> s1 >> s2;
        double mylat, mylon;// cin >> mylat >> mylon;
        mylat = parse(s1);
        mylon = parse(s2);
        string transport; cin >> transport;
        double minutes; cin >> minutes;
        double reach = calc_move(transport, minutes);
        reach = round(reach * 100);
        //cout << "reach " << reach << endl;
        vector<pair<double, int>> attractions;
        for (int i = 0; i < N; ++i) {
            double dist = calc_dist(mylat, mylon, lat[i], lon[i]);
            double rounded_dist = round(dist * 100);
            //if ((long long)dist <= (long long)reach) {
            if (rounded_dist <= reach) {
                //cout << "found: " << dist << ' ' << id[i] << endl;
                attractions.push_back(make_pair(rounded_dist, id[i]));
            }
        }
        sort(attractions.begin(), attractions.end());
        for (int i = 0; i < attractions.size(); ++i) {
            if (i) cout << ' ';
            cout << attractions[i].second;
        }
        cout << endl;
    }
}
