// http://codeforces.ru/contest/8/problem/A
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

#define sz(a) int(a.size())

int match(const string &text, const string &patt)
{
    for(int i=0; i<sz(text); ++i)
    {
        int j;
        for(j=0; j<sz(patt) && i+j < sz(text); ++j)
        {
            if (text[i+j]!=patt[j]) break;
        }
        if (j>=sz(patt)) return i;
    }
    return -1;
}

int main()
{
    string a, b, c; cin >> a >> b >> c;

    int pos = match(a,b);
    bool forward=false, backward=false;
    if (pos>=0) {
        pos = match(a.substr(pos+sz(b)),c);
        if (pos>=0) forward=true;
    }
    reverse(a.begin(), a.end());
    pos = match(a,b);
    if (pos>=0) {
        pos = match(a.substr(pos+sz(b)),c);
        if (pos>=0) backward=true;
    }

    if (forward) {
        if (backward) cout << "both" << endl;
        else cout << "forward" << endl;
    }
    else {
        if (backward) cout << "backward" << endl;
        else cout << "fantasy" << endl;
    }
}

