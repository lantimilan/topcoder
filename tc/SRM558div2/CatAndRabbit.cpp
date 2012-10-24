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

typedef long long int64;

map<int64, bool> dp;

int N;

bool canwin(int64 conf, int turn)
{
    if (conf == (1LL<<N)-1) return false;
    if (dp.find(conf) != dp.end()) return dp[conf];

    for(int i=0; i<N; ++i) if (1LL<<i & conf) { // pos[i] is B
        int64 next;
        // left
        next = conf;
        for(int j=i-1; j>=0 && (1LL<<j & conf) == 0; --j) {
            next |= 1LL<<j;
            if (!canwin(next, 1-turn))
                return dp[conf]=true;
        }
        // right
        next = conf;
        for(int j=i+1; j<N && (1LL<<j & conf) == 0; ++j) {
            next |= 1LL<<j;
            if (!canwin(next, 1-turn))
                return dp[conf] = true;
        }
    }
    return dp[conf] = false;
}

class CatAndRabbit
{ 
public: 
    string getWinner(string tiles) 
    { 
        N = tiles.size();
        int64 conf;
        int n = tiles.size();
        conf = 0;
        for(int i=0; i<n; ++i) {
            int64 val = (tiles[i] == '#');
            conf |= val<<i;
        }
        bool first = canwin(conf, 0);
        if (first) return "Cat";
        else return "Rabbit";
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5();
    if ((Case == -1) || (Case == 6)) test_case_6(); 
    }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "#.."; string Arg1 = "Cat"; verify_case(0, Arg1, getWinner(Arg0)); }
	void test_case_1() { string Arg0 = ".#."; string Arg1 = "Rabbit"; verify_case(1, Arg1, getWinner(Arg0)); }
	void test_case_2() { string Arg0 = "###"; string Arg1 = "Rabbit"; verify_case(2, Arg1, getWinner(Arg0)); }
	void test_case_3() { string Arg0 = "#..##.#"; string Arg1 = "Cat"; verify_case(3, Arg1, getWinner(Arg0)); }
	void test_case_4() { string Arg0 = "..."; string Arg1 = "Rabbit"; verify_case(4, Arg1, getWinner(Arg0)); }
	void test_case_5() { string Arg0 = "###...####....###...####...."; string Arg1 = "Rabbit"; verify_case(5, Arg1, getWinner(Arg0)); }
	void test_case_6() { string Arg0 = "...#...#...#...#...#...#...#...#...#...#...#..."; string Arg1 = "Rabbit"; verify_case(6, Arg1, getWinner(Arg0)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main()
{
    CatAndRabbit __test; 
    __test.run_test(-1); 
} 
// END CUT HERE 
