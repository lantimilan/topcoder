// A.cpp

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char str[1000000+5];

bool is_vowel(char ch)
{
    char vowels[] = "aeiou";
    for (int i = 0; i < 5; ++i) if (ch == vowels[i])
        return true;
    return false;
}

bool is_cons(char ch)
{
    return !is_vowel(ch);
}

void solve(int tcase)
{
    scanf("%s", str); //cout << str << endl;
    int thresh; scanf("%d", &thresh);
    int n = strlen(str);

    long long ans = 0;
    int last;  // last start of previous block
    int p1, p2;  // begin and end of consecutive cons of length <= thresh
    int cnt;

    //cout << str << ' ' << thresh << endl;
    last = -1; p1 = p2 = -1;
    while (true) {
        for (++p1; p1 < n && is_vowel(str[p1]); ++p1) ;
        if (p1 >= n) break;
        bool found = false;
        for (p2 = max(p1, p2); p2 < n && !is_vowel(str[p2]); ++p2) {
            if (p2 - p1 + 1 == thresh) { found = true; break; }
        }
        if (found) {
            ans += 1LL * (p1 - last) * (n - p2);
            last = p1;
        } else {
            p1 = p2;
        }
    }

    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

int main()
{
    int T; scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
        solve(t);
}
