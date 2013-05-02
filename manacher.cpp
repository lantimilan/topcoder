// manacher.cpp
//
// Manacher's algorithm
// O(n) time finds all palindrome substring

#include <cassert>
#include <iostream>
using namespace std;

void manacher(string s, int span[])
{
    int n = s.size();
    int c = 0;  // center
    span[0] = 0;
    for (int i = 1; i < n; ++i) {
        int j = 2*c - i;
        if (j < 0) span[i] = 0;
        else span[i] = min(c+span[c]-i, span[j]);
        if (span[i] < 0) span[i] = 0;
        int l = c - span[c];
        int l1 = j - span[j];
        if (l1 <= l) {
            int p = i + span[i];
            int q = i - span[i];
            while (0 <= q && p < n && s[p] == s[q]) {
                p++; q--;
            }
            span[i] = p - i - 1;
            c = i;
        }
    }
}

void manacher2(const string &s, int len[], int flag=false)
{
    int n = s.size();
    int c[2] = {0, 1};

    for (int i = 0; i < 2*n; ++i) len[i] = 0;
    len[0] = 0; len[1] = 1;

    for (int i = 2; i < 2*n; ++i) {
        int k = c[i&1];
        int l1, l, r, p, q;
        int j = 2*k - i;

        l = (k-len[k])/2;
        r = (k+len[k])/2 - 1;
        if (j<0) {
            len[i] = i & 1;
            l = i/2; r = (i-1)/2;
            l1 = -1;
        } else {
            len[i] = min(len[j], 2*r - i + 2);
            len[i] = max(len[i], i&1);
            l1 = (j-len[j])/2;
        }
        if (l1 > l) continue;  // left image within boundary, len[i] fixed
        p = r-len[i]; q = r+1;
        while (0 <= p && q < n && s[p] == s[q]) {
            p--; q++;
        }
        len[i] = q-p-1;
        if (q-1 > r) c[i&1] = i;  // move center to next pos
    }
    if (flag) {  // show result
    cout << "pal len[]\n";
    for (int i = 0; i < 2*n; ++i) {
        if (i&1) cout << ' ' << s[i/2];
    }
    cout << endl;
    for (int i = 0; i < 2*n; ++i) if (i&1) {
        cout << ' ' << len[i];
    }
    cout << endl;
    for (int i = 0; i < 2*n; ++i) if (i%2 == 0) {
        cout << ' ' << len[i];
    }
    cout << endl;
    }
}

int main()
{
    string s = "abababababassaa";
    int span[30];
    manacher(s, span);
    for (int i = 0; i < s.size(); ++i) {
        int sp = span[i];
        cout << sp << ' ';
    }
    cout << endl;

    int len[30];
    manacher2(s, len, true);
    manacher2("a", len);
    manacher2("", len);

    // test large
    int large[200000*2+5];
    string slarge(200000, 'a');
    manacher2(slarge, large);
}
