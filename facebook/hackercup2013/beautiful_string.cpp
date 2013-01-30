// beautiful_string.cpp
#include <iostream>
#include <string>
using namespace std;

int getval(char ch)
{
    if ('a' <= ch && ch <= 'z') return ch - 'a';
    if ('A' <= ch && ch <= 'Z') return ch - 'A';
    return -1;
}

int main()
{
    int m; cin >> m;
    cin.ignore(1024, '\n');
    for (int i=0; i<m; ++i) {
        string line; getline(cin, line);
        int cnt[30] = {0};
        for (int p=0; p<line.length(); ++p) {
            int v = getval(line[p]);
            if (v >= 0) cnt[v]++;
        }
        int score = 0;
        int mx = 26;
        for (int k=0; k<26; ++k) {
            int x = -1;
            for (int p=0; p<26; ++p) if (cnt[p] > 0) {
                if (x < 0 || cnt[p] > cnt[x])
                    x = p;
            }
            if (x == -1) break;
            score += cnt[x] * (mx--);
            cnt[x] = 0;
        }
        cout << "Case #" << (i+1) << ": " << score << endl;
    }
}
