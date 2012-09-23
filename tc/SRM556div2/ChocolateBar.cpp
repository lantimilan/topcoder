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

class ChocolateBar
{ 
public: 
    int maxLength(string letters) 
    { 
        int n = letters.size();
        int ans = 0;
        for(int i=0; i<n; ++i)
        for(int j=i; j<n; ++j)
        {
        bool good = true;
        int cnt[30] = {0};
        for(int k=i; k<=j; ++k)
        {
            cnt[letters[k]-'a']++;
            if (cnt[letters[k]-'a']>1) good=false;
        }
        if (good) ans = max(ans, j-i+1);
        }
        return ans;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "srm"; int Arg1 = 3; verify_case(0, Arg1, maxLength(Arg0)); }
	void test_case_1() { string Arg0 = "dengklek"; int Arg1 = 6; verify_case(1, Arg1, maxLength(Arg0)); }
	void test_case_2() { string Arg0 = "haha"; int Arg1 = 2; verify_case(2, Arg1, maxLength(Arg0)); }
	void test_case_3() { string Arg0 = "www"; int Arg1 = 1; verify_case(3, Arg1, maxLength(Arg0)); }
	void test_case_4() { string Arg0 = "thisisansrmbeforetopcoderopenfinals"; int Arg1 = 9; verify_case(4, Arg1, maxLength(Arg0)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main()
{
    ChocolateBar __test; 
    __test.run_test(-1); 
} 
// END CUT HERE 
