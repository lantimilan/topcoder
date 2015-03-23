// prob527C.cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

// reduce to 1D.
void process(int split, set<int> &axis, multiset<int> &segments)
{
    set<int>::iterator it = axis.lower_bound(split);
    int end = *it;
    int begin = *--it;
    multiset<int>::iterator mit = segments.find(end - begin);
    segments.erase(mit);
    segments.insert(end - split);
    segments.insert(split - begin);
    axis.insert(split);
}

int main()
{
    int w, h, n; cin >> w >> h >> n;
    set<int> hor, ver;
    hor.insert(0); hor.insert(h);
    ver.insert(0); ver.insert(w);

    multiset<int> hspace, vspace;
    hspace.insert(h); vspace.insert(w);

    for (int i = 0; i < n; ++i) {
        string op; int val;
        cin >> op >> val;
        if (op[0] == 'H') {  // horizontal
            process(val, hor, hspace);
        } else {  // vertical
            process(val, ver, vspace);
        }
        multiset<int>::iterator horit, verit;
        horit = --hspace.end();
        verit = --vspace.end();
        cout << 1LL * (*horit) * (*verit) << endl;
    }
}
