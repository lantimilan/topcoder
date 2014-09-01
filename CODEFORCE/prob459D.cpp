// prob459D.cpp

#include <iostream>
#include <map>

using namespace std;

int a[1000000+5];
map<int, int> mp;

int forward[1000000+5];
int backward[1000000+5];

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    mp.clear();
    for (int i = 0; i < n; ++i) {
        mp[a[i]]++;
        forward[i] = mp[a[i]];
    }
    mp.clear();
    for (int i = n-1; i >= 0; --i) {
        mp[a[i]]++;
        backward[i] = mp[a[i]];
    }
}
