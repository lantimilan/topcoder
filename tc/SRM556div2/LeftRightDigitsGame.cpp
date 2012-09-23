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

string dp1[60];  // best of prefix n with or without leading zero
string dp2[60];  // best of prefix n without leading zero

class LeftRightDigitsGame
{ 
public: 
    void update(string &s, const string& val)
    {
        if (s[0]=='X') { s = val; return; }
        if (s>val) { s = val; return; }
    }
    string minNumber(string digits) 
    { 
        int n = digits.size();
        for(int i=0; i<=n; ++i)
            dp1[i] = dp2[i] = "X";
        dp1[0] = dp2[0] = "";
        for(int i=1; i<=n; ++i) {
            string s1 = dp1[i-1] + string(1,digits[i-1]); 
            string s2 = string(1,digits[i-1]) + dp1[i-1];
            dp1[i] = min(s1, s2);
            if (s1[0] != '0') update(dp2[i], s1);
            if (s2[0] != '0') update(dp2[i], s2);
            if (dp2[i-1][0] != 'X') {
                if (digits[i-1] == '0') {
                    if (dp2[i-1] != "") {
                        update(dp2[i], dp2[i-1] + "0");
                    }
                } else {
                    update(dp2[i], dp2[i-1] + string(1,digits[i-1]));
                    update(dp2[i], string(1,digits[i-1]) + dp2[i-1]);
                }
            }
            cout << dp1[i] << ' ' << dp2[i] << endl;
        }
        return dp2[n];
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1();
    if ((Case == -1) || (Case == 2)) test_case_2(); 
    if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "565"; string Arg1 = "556"; verify_case(0, Arg1, minNumber(Arg0)); }
	void test_case_1() { string Arg0 = "9876543210"; string Arg1 = "1234567890"; verify_case(1, Arg1, minNumber(Arg0)); }
	void test_case_2() { string Arg0 = "8016352"; string Arg1 = "1086352"; verify_case(2, Arg1, minNumber(Arg0)); }
	void test_case_3() { string Arg0 = "01"; string Arg1 = "10"; verify_case(3, Arg1, minNumber(Arg0)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main()
{
    LeftRightDigitsGame __test; 
    __test.run_test(-1); 
} 
// END CUT HERE 
