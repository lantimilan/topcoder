// prob351B.cpp
//
// since each operation is indepdent, we consider them separately
//
// first consider a simpler question, how many swaps of adjacent elements
// needed to sort a permutation?
// A: #inv, because each swap reduce #inv by exactly 1
//
// now it is clear
// Let inv be the number of inversion of the input perm
// when Jeff makes a move, he can reduce inv by 1
// when Furik makes a move, he has pr = 0.5 to incr inv by 1
// and pr = 0.5 to decr inv by 1
//
// base case E[0] = 0 because no move is needed
// base case E[1] = 1 because Jeff will make the swap so that the game ends
// recurrence:
// E[inv] = 2 + 0.5 * E[inv -2] + 0.5 * E[inv]
// so E[inv] = 4 + E[inv - 2]
// since n <= 3000, we can even use the O(n^2) algorithm to count inv

#include <algorithm>
#include <cstdio>
#include <iterator>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n; cin >> n;
    vector<int> perm;
    istream_iterator<int> eos;
    istream_iterator<int> is(cin);
    copy(is, eos, back_inserter(perm));

    int inv = 0;
    for (int i = 0; i < perm.size(); ++i) {
        for (int j = i+1; j < perm.size(); ++j) {
            if (perm[i] > perm[j]) inv++;
        }
    }
    int a, b, c;
    a = 0; b = 1;
    if (inv == 0) c = a;
    else if (inv == 1) c = b;
    else {
        for (int i = 2; i <= inv; ++i) {
            c = 4 + a;
            a = b; b = c;
        }
    }
    printf("%.6f\n", c*1.0);
}

