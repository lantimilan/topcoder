// prob280B.cpp
//
// maintain a stack with falling subsequence
// a[i] kills all tails that less than a[i], update xor
// a[i] serves as second maximum exactly when it was popped out of stack
// it pairs with top of stack if any, which serves as max to the left
// it then pairs with the item that kills it, serves max to the right

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
using namespace std;

stack<int> st;
int a[100000+5];

int main()
{
    int n; cin >> n;
    for (int i=0; i<n; ++i) cin >> a[i];
    int best = 0;
    int pos;
    // left to right
    pos = 0;
    st.push(a[pos++]);
    while (pos < n) {
        while (!st.empty() && a[pos] > st.top()) {
            int item = st.top();
            int cur = a[pos] ^ item; st.pop();
            best = max(best, cur);
            if (!st.empty()) {
                cur = item ^ st.top();
                best = max(best, cur);
            }
        }
        st.push(a[pos++]);
    }
    if (!st.empty()) {
        int first = st.top(); st.pop();
        while(!st.empty()) {
            int second = st.top(); st.pop();
            int cur = first ^ second;
            best = max(best, cur);
            first = second;
        }
    }
    // right to left, not necessary
    // before the issue was popped item not checked
    // against stack top
    /*
    assert(st.empty());
    pos = n-1;
    st.push(a[pos--]);
    while (pos >= 0) {
        while (!st.empty() && a[pos] > st.top()) {
            int cur = a[pos] ^ st.top(); st.pop();
            best = max(best, cur);
        }
        st.push(a[pos--]);
    }
    if (!st.empty()) {
        int first = st.top(); st.pop();
        while(!st.empty()) {
            int second = st.top(); st.pop();
            int cur = first ^ second;
            best = max(best, cur);
            first = second;
        }
    }
    */

    cout << best << endl;
}

// Accepted
