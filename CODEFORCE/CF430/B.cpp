// B.cpp

#include <iostream>
#include <vector>
using namespace std;

int process(vector<int> balls, int pos, int color)
{
    int size = balls.size();
    vector<int> tmp;
    for (int i = 0; i < pos; ++i) tmp.push_back(balls[i]);
    tmp.push_back(color);
    for (int i = pos; i < balls.size(); ++i) tmp.push_back(balls[i]);

    while (true) {
        int start = -1, end = -1;
        for (int i = 0; i < tmp.size(); ++i) {
            int target = tmp[i];
            int j;
            for (j = i; j < tmp.size(); ++j) {
                if (tmp[j] != target) break;
            }
            if (j - i >= 3) {
                start = i; end = j;
                break;
            }
        }
        if (start < 0) break;
        // erase [start..start+3)
        vector<int> tmp2;
        for (int i = 0; i < tmp.size(); ++i) {
            if (start <= i && i < end) {}
            else tmp2.push_back(tmp[i]);
        }
        tmp = tmp2;
    }
    return size - tmp.size();
}

int main()
{
    vector<int> balls;
    int n, k, x; cin >> n >> k >> x;
    balls.resize(n);
    for (int i = 0; i < n; ++i) cin >> balls[i];

    int ans = 0;
    for (int i = 1; i < n; ++i)
        ans = max(ans, process(balls, i, x));
    cout << ans << endl;
}
