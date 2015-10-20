// server.cpp
#include <iostream>
using namespace std;

int main() {
    int tcase = 0;
    int n, T;
    while (cin >> n >> T) {
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            int task; cin >> task;
            if (task > T) {
                T = 0;
            } else {
                T -= task;
                cnt++;
            }
        }
        cout << "Case " << (++tcase) << ": ";
        cout << cnt << endl;
    }
}
