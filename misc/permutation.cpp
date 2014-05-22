// permutation.cpp

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

template<class T>
void myswap(T &x, T &y)
{
    T tmp = x; x = y; y = tmp;
}

template<class T>
bool next_permutation(vector<T> &v)
{
    int i, j;
    for (i = v.size()-1; i-1 >= 0; --i) {
        if (v[i-1] < v[i]) break;
    }
    if (i-1 < 0) return false;
    for (j = v.size()-1; j >= i; --j) {
        if (v[j] > v[i-1]) break;
    }
    assert(j >= i);
    myswap(v[i-1], v[j]);
    for (int k = i, l = v.size()-1; k < l; ++k, --l) {
        myswap(v[k], v[l]);
    }
    return true;
}

template<class T>
void print(const vector<T> &v)
{
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
    cout << endl;
}


int main()
{
    cout << "A = {1,2,3,4}, cnt = 24" << endl;
    int acnt = 24;
    int a[] = {1,2,3,4};
    vector<int> v(a, a + sizeof(a)/sizeof(a[0]));
    do {
        print(v); acnt--;
    } while (next_permutation(v));
    assert(acnt == 0);

    cout << "B = {1,2,2,4}, cnt = 12" << endl;
    int bcnt = 24 / 2;
    int b[] = {1,2,2,4};
    vector<int> w(b, b + sizeof(b)/sizeof(b[0]));
    do {
        print(w); bcnt--;
    } while (next_permutation(w));
    assert(bcnt == 0);
}
