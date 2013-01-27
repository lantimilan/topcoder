// p1011.cpp

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s[2];
    while (cin >> s[0] >> s[1]) {
        // pad to xx.00
        for (int x=0; x<2; ++x) {
            int p, l = s[x].length();
            for (p=0; p<l; ++p)
                if (s[x][p] == '.') break;
            if (p>=l) s[x] += ".00";
            else s[x] += string(2-(l-p-1), '0');
        }
        //cout << s[0] << ' ' << s[1] << endl;
        int a[2] = {0};
        for (int x=0; x<2; ++x) {
            for (int p=0; p<s[x].length(); ++p)
                if (s[x][p] != '.')
                    a[x] = 10*a[x] + s[x][p]-'0';
        }
        //cout << a[0] << ' ' << a[1] << endl;

        const int deno = 10000;
        int n;
        for (n=1; ; ++n) {
            int b[2];
            b[0] = a[0] * n / deno + 1;  // floor + 1
            b[1] = (a[1] * n + deno-1) / deno - 1;  // ceil - 1
            if (b[1] >= b[0]) break;
        }
        cout << n << endl;
    }
}

// 4742126  14:58:31 27 Jan 2013
// lantimilan  1011. Conductors    C++ Accepted    0.015   180 KB
