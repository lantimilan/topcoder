// A.cpp

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int,int> pii;
typedef pair<pii, pii> pp;

int N;
int X1, Y1, X2, Y2;
pp rects[6];

int main()
{
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        rects[i].first.first  = x1;
        rects[i].first.second = y1;
        rects[i].second.first = x2;
        rects[i].second.second = y2;

        if (i == 0) {
            X1 = x1; Y1 = y1; X2 = x2; Y2 = y2;
        } else {
            X1 = min(X1, x1); Y1 = min(Y1, y1);
            X2 = max(X2, x2); Y2 = max(Y2, y2);
        }
    }
    //cout << X1 << ' ' << Y1 << ' ' << X2 << ' ' << Y2 << endl;

    bool ans = true;
    for (int yy = Y1; yy < Y2; yy++) {
        double y = yy + .5;
        //cout << y << endl;
        vector<pii> row;
        for (int i = 0; i < N; ++i) {
            int x1, y1, x2, y2;
            x1 = rects[i].first.first;
            y1 = rects[i].first.second;
            x2 = rects[i].second.first;
            y2 = rects[i].second.second;
            //cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
            if (y1 <= y && y <= y2) {
                vector<pii> row2;
                int k;
                for (k = 0; k < row.size(); ) {
                    int t1, t2;
                    t1 = row[k].first; t2 = row[k].second;
                    if (t2 < x1) {
                        row2.push_back(row[k++]);
                    } else if (t1 <= x2) {
                        pii p(min(t1, x1), max(t2, x2));
                        row2.push_back(p);
                        while (k < row.size() &&
                               row[k].first <= row2.back().second) {
                               int t1, t2;
                               t1 = row2.back().second;
                               t2 = row[k].second;
                               row2.back().second = max(t1, t2);
                               k++;
                        }
                    } else break;
                }
                if (row.empty() || row.back().second < x1)
                    row2.push_back(pii(x1, x2));
                for (; k < row.size(); ++k) row2.push_back(row[k]);
                row = row2;
            }
        }
        if (row.size() != 1 || row[0].first != X1 || row[0].second != X2) {
            //cout << y << ": ";
            //for (int i = 0; i < row.size(); ++i)
            //    cout << row[i].first << ' ' << row[i].second << " -- ";
            //cout << endl;
            ans = false; break;
        }
    }
    if (X2 - X1 != Y2 - Y1) ans = false;
    if (ans) cout << "YES\n";
    else cout << "NO\n";
}
