// dirtiness.cpp
#include <iostream>
#include <set>
#include <utility>
using namespace std;

typedef pair<int,int> PII;
set<PII> leftset, rightset;

int main() {
    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        leftset.clear();
        rightset.clear();
        for (int i = 0; i < N; ++i) {
            leftset.insert(make_pair(0, i));
            rightset.insert(make_pair(0, -i));
        }
        int pos = 0, dirty = 0;
        for (int i = 1; i <= M; ++i) {
            PII p;
            if (i & 1) {  // use cleanest from left
                p = *(leftset.begin());
            } else {  // use cleanest from right
                p = *(rightset.begin());
            }
            dirty = p.first, pos = p.second;
            int leftpos = abs(pos);
            int rightpos = -abs(pos);
            leftset.erase(make_pair(dirty, leftpos));
            leftset.insert(make_pair(dirty+1, leftpos));
            rightset.erase(make_pair(dirty, rightpos));
            rightset.insert(make_pair(dirty+1, rightpos));
        }
        cout << (abs(pos)+1) << ' ' << dirty << endl;
    }
}
