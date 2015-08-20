// poinonous.cpp
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// find surivors are easy, a[0] must be one, then look right to find first
// a[i] such that a[0] >= a[i], then repeat
//
// The key is: if a[i] is killed by a[j], then a[j] has to overcome all
// elements in between to reach a[i], in other words, the max days to
// kill any in between elements, call it d, then a[i] is killed at day d+1
//
// use a stack (a[i], day_killed)
// example:
// 1, 5, 7, 10, 9, 8, 9, 6
// stack
// (1,0) (5,1) (7,1) (10,1)
// (1,0) (5,1) (7,1) (9,2)
// (1,0) (5,1) (7,1) (8,3)
// (1,0) (5,1) (7,1) (8,3) (9,1)
// (1,0) (5,1) (6,4)
//
// Observation:
// 1. a[i] is killed by the first one to its left that is smaller, say a[j]
// 2. for a[j] to reach a[i], a[j] must get rid of all a[j+1..i-1], so the
// day a[i] killed by a[j] would be the max of the in-between elements death
// days plus 1.

int a[100000+5];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    stack<pair<int,int>> st;
    st.push(make_pair(a[0], 0));
    int most = 0;
    for (int i = 1; i < n; ++i) {
        int cur = 0;
        while (!st.empty()) {
            pair<int,int> p = st.top();
            int val = p.first;
            int day = p.second;
            if (val < a[i]) {  // found the killer of a[i]
                st.push(make_pair(a[i], cur+1));
                most = max(most, cur+1);
                break;
            } else {
                st.pop();
                cur = max(cur, day);
            }
        }
        if (st.empty()) {
            st.push(make_pair(a[i], 0));
        }
    }
    cout << most << endl;
}
