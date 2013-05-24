#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define sz(a) int(a.size())

class ShuffleSort
{ 
public: 
    double shuffle(vector <int> cards) 
    { 
        double E[60];
        int N = cards.size();
        sort(cards.begin(), cards.end());
        for (int i = 0; i <= N; ++i) E[N] = 0.0;
        for (int i = N-1; i >= 0; --i) {
            int mm = 0;
            int val = cards[i];
            for (int j = i; j < N; ++j) {
                if (cards[j] == val) mm++;
                else break;
            }
            E[i] = 1;
            int l = N - i;
            if (mm < l) {
                double prob = 1.0 * (l - mm) / l;
                for (int p = 1; p+1 < l; ++p) {  // first p min then a non-min
                    double pr = 1.0;
                    int pos = i + mm;
                    int t = mm;
                    // number of ways to choose first p
                    for (int k = 0; k < p; ++k) {
                        if (t <= 0) {
                            int x;
                            for (x = pos; x < N; ++x)
                                if (cards[x] > cards[pos]) break;
                            t = x - pos;
                            pos = x;
                        }
                        pr *= t--;
                    }
                    // now choose the blocker
                    int first;
                    if (t == 0) {
                        first = N-1;
                        while (cards[first] > cards[pos]) first--;
                        first++;
                    } else { first = pos; }
                    int rem = N - first;
                    pr *= rem;

                    for (int x = 0; x <= p; ++x) pr /= (l-x);
                    E[i] += pr * E[i+p];
                    //cout << "p " << p << " " << pr << " " << E[i+p] << endl;
                }
                E[i] /= (1.0 - prob);
            }
            cout << "E[" << i << "] " << E[i] << endl;
        }
        return E[0];
    } 
    
 
}; 



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
