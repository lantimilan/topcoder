// stringalgo.cpp
//
// algorithm for string matching

// Z-algorithm
// Z[i] is length of longest substring starting at i that is a prefix of S[]

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

void Zalgo(const string &S, int Z[])
{
    Z[0] = -1;
    int i, j, k;
    int N = S.size();
    int L, R;
    int pos = 1;
    for (i=pos, j=0; i < N && S[i] == S[j]; ++i, ++j) ;
    Z[pos] = i-pos;

    L = pos; R = i;

    for (i = 2; i < N; ++i) {
        if (i < R) {
            assert(i >= L);
            Z[i] = Z[i - L];
            if (Z[i] + i >= R) {
                for (j = R, k = R-L; j < N && S[j] == S[k]; ++j, ++k) ;
                Z[i] = j - i;
                L = i; R = j;
            }
        } else {
            for (j = i, k = 0; j < N && S[j] == S[k]; ++j, ++k) ;
            Z[i] = j - i;
            L = i; R = j;
        }
    }
}

int main()
{
    int Z[300];
//    string S = "aabcdaabcxy";
    string S = "aab" + string("$") + "aabcdaabcxy";  // string matching aab to the one after $
    Zalgo(S, Z);
    for (int i = 0; i < S.size(); ++i) cout << ' ' << S[i];
    cout << endl;
    for (int i = 0; i < S.size(); ++i) cout << Z[i] << ' ';
    cout << endl;
}
