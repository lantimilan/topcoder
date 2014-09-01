// prob457A.cpp
// memsql R2
//
// OJ practice not up
//
// algorithm:
// prepend with leading zeros to make two string equal length
// skip pos with same digit
// when differ, one is '1' and the other is '0', then it must be 100 = 011
// or we already know which one is bigger

#include <iostream>
#include <string>
using namespace std;

string s[2];

int main()
{
    cin >> s[0] >> s[1];
    int n1 = s[0].length();
    int n2 = s[1].length();
    int n = max(n1, n2);
    s[0] = string(n-n1, '0') + s[0];
    s[1] = string(n-n2, '0') + s[1];

    //cout << s[0] << ' ' << s[1] << endl;

    int ans = 0;
    for (int pos = 0; pos < n; ) {
        while (pos < n && s[0][pos] == s[1][pos]) pos++;
        if (pos >= n) {
            ans = 0; break;
        }
        int small, large;
        if (s[0][pos] == '1') { large = 0; small = 1;}
        else { small = 0; large = 1; }

        if (pos + 2 < n &&
            s[large][pos+1] == '0' && s[large][pos+2] == '0' &&
            s[small][pos+1] == '1' && s[small][pos+2] == '1') {
                pos += 3;
            } else {
                ans = large == 0 ? 1 : -1;
                break;
            }
    }
    if (ans == 1) cout << ">" << endl;
    else if (ans == 0) cout << "=" << endl;
    else cout << "<" << endl;
}
