// prob493D.cpp
// strategy
// number of column does not matter
// consider 1xn
// n = 2, white move to right and win
// n = 3, black win
// n = 4, white win
// n = 5, black win
// symmetry, if n is odd, then black can mimic white until white enters center lane
// if n is even, then white moves to column=2 and then mimic black

#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    string white = "white";
    string black = "black";
    if (n % 2 == 0) {
        cout << white << endl;
        cout << "1 2" << endl;
    } else {
        cout << black << endl;
    }
}
