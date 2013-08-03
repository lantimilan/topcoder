// B.cpp

#include <cstring>
#include <string>
#include <iostream>
#include <map>
using namespace std;

string s;

typedef pair<int,int> pii;

int pal[2605][2605];
int match[2605][2605];

int calc(int a, int b)
{
    if (a > b) return 0;
    if (a == b) return 1;
    if (pal[a][b] >= 0) return pal[a][b];

    int len[3];
    len[0] = calc(a, b-1);
    len[1] = calc(a+1, b);
    len[2] = calc(a+1, b-1);
    if (s[a] == s[b]) len[2] += 2;

    int mm;
    int ans;
    mm = 0; ans = len[0];
    if (len[1] > ans) { ans = len[1]; mm = 1; }
    if (len[2] > ans) { ans = len[2]; mm = 2; }
    match[a][b] = mm;
    return pal[a][b] = ans;
}

string getpal(int a, int b)
{
    if (a > b) return "";
    if (a == b) return string(1, s[a]);
    if (match[a][b] == 0) return getpal(a, b-1);
    if (match[a][b] == 1) return getpal(a+1, b);
    string ans = getpal(a+1, b-1);
    if (s[a] == s[b]) ans = string(1, s[a]) + ans + string(1, s[b]);
    return ans;
}

int main()
{
    cin >> s;
    int len = s.length();
    if (len >= 2600) {
        int ch = -1;
        for (int x = 0; x < 26; ++x) {
            int cnt = 0;
            for (int p = 0; p < len; ++p) cnt += (s[p] == char(x +'a'));
            if (cnt >= 100) { ch = char(x + 'a'); break; }
        }
        cout << string(100, ch) << endl;
        return 0;
    }
    memset(pal, -1, sizeof pal);
    int ans = calc(0, len-1);
    //cout << ans << endl;
    string strans = getpal(0, len-1);
    if (strans.length() > 100) {
        string tmp = strans.substr(0,50);
        string tmp2 = strans.substr(strans.length()-50);
        cout << tmp + tmp2 << endl;
    } else {
        cout << strans << endl;
    }
}
