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

// BFS
//
//
set<int> seen;

class TheNumberGameDiv2
{ 
public: 
    int rev(int n)
    {
        assert(n != 0);
        int ans = 0;
        while (n) {
            int d = n % 10;
            ans = ans * 10 + d;
            n /= 10;
        }
        return ans;
    }

    int minimumMoves(int A, int B) 
    { 
        queue< pair<int,int> > que;
        que.push(make_pair(A, 0)); seen.insert(A);
        while (!que.empty()) {
            pair<int,int> pa = que.front(); que.pop();
            int node = pa.first;
            int dist = pa.second;
            if (node == B) return dist;
            int next;
            next = rev(node);
            if (next > 0 && !seen.count(next)) {
                que.push(make_pair(next, dist+1));
                seen.insert(next);
            }
            next = node / 10;
            if (next > 0 && !seen.count(next)) {
                que.push(make_pair(next, dist+1));
                seen.insert(next);
            }
        }
        return -1;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 25; int Arg1 = 5; int Arg2 = 2; verify_case(0, Arg2, minimumMoves(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 5162; int Arg1 = 16; int Arg2 = 4; verify_case(1, Arg2, minimumMoves(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 334; int Arg1 = 12; int Arg2 = -1; verify_case(2, Arg2, minimumMoves(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 218181918; int Arg1 = 9181; int Arg2 = 6; verify_case(3, Arg2, minimumMoves(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 9798147; int Arg1 = 79817; int Arg2 = -1; verify_case(4, Arg2, minimumMoves(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main()
{
    TheNumberGameDiv2 __test; 
    __test.run_test(-1); 
} 
// END CUT HERE 
