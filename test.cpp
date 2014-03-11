#include <iostream>
#include <set>
using namespace std;

int main()
{
    int a[] = {1, 2, 3, 4};
    set<int> st;
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
        st.insert(a[i]);
    set<int>::iterator it = st.lower_bound(3);
    int cnt = 0;
    while (it != st.begin()) {
        --it; ++cnt;
    }
    cout << cnt << endl;
}
