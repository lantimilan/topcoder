// B.cpp
//
// This idea, however, is wrong
// for each m = 1 to N
// do selection sort on A[0..m-1] and A[m-1..N-1]
// to count number of swaps needed
//
// counter example
// 70 80 90 1000 910..900 100 800..700
// the optimal solution is to move 100 to the left of 1000 and we are done
// however, the above idea cannot find such a solution, if it puts 100 to the
// right half, then 100 have to travel a long way to the right end
// if it puts 100 to the left half, then 910..900 needs to be reversed
// and that would be roughly (k choose 2) = (11 choose 2), at least 50
//
// One correct idea:
// since we have to put min to either left end or right end, we move it to
// the closer of the two options, after that we can get rid of min and
// do the same on the other n-1 elements
//
// If you do not come up with this idea, you could try DP
// the problem is, how do you go from n-1 elements to n elements


#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

// incresing
int countSwap1(const vector<int> &all, int begin, int end) {
    vector<int> vec;
    for (int i = begin; i < end; ++i) vec.push_back(all[i]);
    int n = vec.size();
    int nswap = 0;
    /*
    for (int i = 0; i < n; ++i) {
        int minpos = i;
        for (int j = i+1; j < n; ++j) {
            if (vec[j] < vec[minpos]) minpos = j;
        }
        nswap += minpos - i;
        // move vec[minpos] to pos = i
        int val = vec[minpos];
        for (int j = minpos; j > i; --j) vec[j] = vec[j-1];
        vec[i] = val;
    }
    for (int i = 0; i < n-1; ++i) assert(vec[i] < vec[i+1]);
    */
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (vec[i] > vec[j]) nswap++;
    return nswap;
}

// decreasing
int countSwap2(const vector<int> &all, int begin, int end) {
    vector<int> vec;
    for (int i = begin; i < end; ++i) vec.push_back(all[i]);
    //cout << endl << "countswap2 " << begin << ' ' << end << endl;
    //for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' '; cout << endl;
    int n = vec.size();
    int nswap = 0;
    /*
    for (int i = 0; i < n; ++i) {
        int maxpos = i;
        for (int j = i+1; j < n; ++j) {
            if (vec[j] > vec[maxpos]) maxpos = j;
        }
        nswap += maxpos - i;
        // move vec[i] to vec[minpos]
        int val = vec[maxpos];
        for (int j = maxpos; j > i; --j) vec[j] = vec[j-1];
        vec[i] = val;
        //cout << "i = " << i << ": " << nswap << ' ';
        //for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' '; cout << endl;
    }
    //cout << endl << "countswap2 " << begin << ' ' << end << ' ' << nswap << endl;
    for (int i = 0; i < n-1; ++i) assert(vec[i] > vec[i+1]);
    */
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (vec[i] < vec[j]) nswap++;
    return nswap;
}
void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    int nswap = 0;
    for (int i = 0; i < N; ++i) {
        int minpos = 0;
        for (int j = 1; j < A.size(); ++j) {
            if (A[j] < A[minpos]) minpos = j;
        }
        int d1 = minpos, d2 = A.size() - minpos -1;
        if (d1 < d2) {
            // move to left end
            nswap += d1;
        } else {
            // move to right end
            nswap += d2;
        }
        A.erase(A.begin() + minpos);
    }
    cout << nswap << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
