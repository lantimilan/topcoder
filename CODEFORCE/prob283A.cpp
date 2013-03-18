// prob283A.cpp

#include <iomanip>
#include <iostream>
using namespace std;

int a[200000+10];
int extra[200000+10];

int main()
{
    int n; cin >> n;
    int cnt = 1;
    long long sum = 0;
    for (int i=0; i<n; ++i) {
        int ti, ai, xi, ki;
        cin >> ti;
        switch (ti) {
            case 1: cin >> ai >> xi;  // a[0..ai-1] += xi
                sum += ai * xi;
                extra[ai-1] += xi;
                break;
            case 2: cin >> ki;  // push back
                sum += ki;
                a[cnt++] = ki;
                break;
            case 3:  // pop back
                cnt--;
                extra[cnt-1] += extra[cnt];
                sum -= (a[cnt] + extra[cnt]);
                extra[cnt] = 0;
                break;
        }
        cout << fixed << setprecision(9) << 1.0 * sum / cnt << endl;
    }
}

// Accepted
