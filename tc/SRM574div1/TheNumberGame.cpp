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

struct state {
    int a, b;
    int turn;
    int move;
};

bool operator<(const state &s1, const state &s2)
{
    if (s1.a != s2.a) return s1.a < s2.a;
    if (s1.b != s2.b) return s1.b < s2.b;
    if (s1.turn != s2.turn) return s1.turn < s2.turn;
    if (s1.move != s2.move) return s1. move < s2.move;
    return false;
}

map<state, bool> memo;

int rev(int a)
{
    int b = 0;
    while (a) {
        b = b * 10 + a % 10;
        a /= 10;
    }
    return b;
}

bool check(int a, int b, int turn, int move)
{
    if (move >= 1000) return turn == 1;
    if (a == b) return turn == 0;
    state st = {a, b, turn, move};
    if (memo.count(st)) return memo[st];

    bool &ans = memo[st];
    // rev a
    if (turn == 0) {
        int a2 = rev(a);
        if (!check(a2, b, 1-turn, move+1)) return ans = true;
        if (!check(a/10, b, 1-turn, move+1)) return ans = true;
    } else {
        int b2 = rev(b);
        if (!check(a, b2, 1-turn, move+1)) return ans = true;
        if (!check(a, b/10, 1-turn, move+1)) return ans = true;
    }
    return ans = false;
}


class TheNumberGame
{ 
public: 
    string determineOutcome(int A, int B) 
    { 
        bool ans = check(A, B, 0, 1);
        if (ans) return "Manao wins";
        else return "Manao loses";
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 45; int Arg1 = 4; string Arg2 = "Manao wins"; verify_case(0, Arg2, determineOutcome(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 45; int Arg1 = 5; string Arg2 = "Manao wins"; verify_case(1, Arg2, determineOutcome(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 99; int Arg1 = 123; string Arg2 = "Manao loses"; verify_case(2, Arg2, determineOutcome(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2356236; int Arg1 = 5666; string Arg2 = "Manao loses"; verify_case(3, Arg2, determineOutcome(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main()
{
    TheNumberGame __test; 
    __test.run_test(-1); 
} 
// END CUT HERE 
