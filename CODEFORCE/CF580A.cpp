// CF580A.cpp
#include <iostream>
#include <map>
using namespace std;

int a[100000+5];
map<int,int> len2key;
map<int,int> key2len;

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0; i < n; ++i) {
        map<int,int>::iterator it = key2len.upper_bound(a[i]);
        if (it == key2len.end()) {
            --it;
            int len = it->second + 1;
            key2len[a[i]] = len;
            len2key[len] = a[i];
        } else {
            if (*it == a[i]) {
                if (++it == seq.end()) {
                    len = max(len, 1 + seq.size());
                }
            } else {
                if (++it != seq.end()) {
                    seq.erase(*it);
                }
            }
        }
        seq.insert(a[i]);
        cout << len << ' ' << a[i] << endl;
    }
    cout << len << endl;
}
