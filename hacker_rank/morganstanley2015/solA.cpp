#include <iostream>
#include <vector>

using namespace std;

int n;

vector<int> v;

int res = 0;

void solve(vector<int> arr, int i) {
    if (i == n) {
        int s = 0;

        for (int i = 0; i < n / 2; i++) {
            s += abs(arr[i] - arr[n - i - 1]);
        }

        if (res < s) {
            res = s;
        }
    } else {
        if (i == 0) {
            arr.push_back(v[i]);

            solve(arr, i + 1);
        } else if (i == (n - 1)) {
            arr.push_back(v[i]);

            solve(arr, i + 1);
        } else {
            arr.push_back(v[i]);

            solve(arr, i + 1);

            arr.pop_back();

            if (! (arr[i - 1] & 1) && ! (v[i + 1] & 1)) {
                int e = (arr[i - 1] + v[i + 1]);

                e /= 2;

                arr.push_back(e);

                solve(arr, i + 1);
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;

    while (t--) {
        v.clear();

        cin >> n;

        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;

            v.push_back(a);
        }

        res = 0;

        solve(vector<int>(), 0);

        cout << res << "\n";
    }

    return 0;
}
