// SNCKYEAR.cc
#include <iostream>
using namespace std;

int main() {
    const int years[] = {2010, 2015, 2016, 2017, 2019};
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        bool hosted = false;
        for (int i = 0; i < sizeof(years)/sizeof(years[0]); ++i) {
            if (N == years[i]) {
                hosted = true;
                break;
            }
        }
        cout << (hosted ? "HOSTED" : "NOT HOSTED") << endl;
    }
}
