// C.cpp
//
// if one free cell, done
// else at least one cell is 0, then place that 0 at corner
// use 3 neighbors around, then arrange the rest continuously with mines

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
