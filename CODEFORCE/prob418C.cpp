// prob418C.cpp
//
// the problem can be reduced to 1D
// suppose you have an array of numbers a[0..n-1] such that
// sum_{i=0}^{n-1} a[i]^2 = k^2
// and similarly an array b[0..m-1] such that sum of square is a square
// then you can use this array to build a table with permutation
// each entry = a[i] * b[j]
// now for each row, the sum is a[i] * b[1], a[i] * b[2], ...
// for each col, the sum is a[1] * b[j], a[2] * b[j], ...
//
// now the hard part is to find n positive integers small enough,
// that is, no more than 10^8
// if there is no such limit, then the following recursive idea will work
// start with 3 and 4, then we know the sum is 5^2, now look for next number
// we can use 12, because 5^2 + 12^2 = 13^2
// next one will be y^2 - x^2 = 13^2 = 169, also y-x=1 since y != x
// so y = (169+1)/2 = 85, and x = 84, so next element is 84
// but this will soon exceed 10^8
// the idea is then to use a lot of 1's when n is big enough.
// This is tourist's construction
//
// for large enough n
// if n is even, target is (n/2)^2 - (n/2 -1)^2 = n-1
// if n is odd, target is ((n+3)/2)^2 - ((n+1)/2)^2 = n + 2 = n-2 + 4 = n-2+2^2
// basecase is n=1, use 1
// n=2 use 3,4


#include <iostream>
#include <vector>
using namespace std;

vector<int> gen(int k)
{
    vector<int> ret;
    if (k == 1) ret.push_back(1);
    else if (k == 2) { ret.push_back(3); ret.push_back(4); }
    else {
        if (k & 1) {
            for (int i = 0; i < k-2; ++i) ret.push_back(1);
            ret.push_back(2);
            ret.push_back((k+1)/2);
        } else {
            for (int i = 0; i < k-1; ++i) ret.push_back(1);
            ret.push_back(k/2 - 1);
        }
    }
    return ret;
}

int main()
{
    int n, m; cin >> n >> m;
    vector<int> a = gen(n);
    vector<int> b = gen(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j) cout << ' ';
            cout << a[i] * b[j];
        }
        cout << endl;
    }
}
