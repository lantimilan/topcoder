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

class TheExperimentDiv2
{ 
public: 
    vector <int> determineHumidity(vector <int> intensity, int L, vector <int> leftEnd) 
    { 
        int N = intensity.size();
        vector<int> ans(leftEnd.size(), 0);
        for (int p = 0; p < N; ++p) {
            for (int i = 0; i < leftEnd.size(); ++i) {
                int a, b;
                a = leftEnd[i]; b = leftEnd[i] + L;
                if (a <= p && p < b) {
                    ans[i]+=intensity[p]; break;
                }
            }
        }
        return ans;
    } 
    
 
}; 



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
