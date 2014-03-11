// bday-gift.cpp
//
// linearity of expectation
// expected = sum of all balls / 2.0

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int N; cin >> N;
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        int num; cin >> num;
        sum += num;
    }
    sum /= 2.0;
    cout << fixed << setprecision(1) << sum << endl;
}
