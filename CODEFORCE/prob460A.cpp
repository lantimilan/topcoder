// prob460A.cpp

#include <iostream>
using namespace std;

int main()
{
    int n, m; cin >> n >> m;
    int cycle = 0;
    int socks = n;
    int days = 0;

    while (socks > 0) {
        cycle++;
        if (cycle % m == 0) socks++;
        socks--;
        days++;
    }
    cout << days << endl;
}
