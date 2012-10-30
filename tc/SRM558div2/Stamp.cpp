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

class Stamp
{ 
public: 
    int getid(char ch)
    {
        switch(ch) {
        case 'R': return 0;
        case 'G': return 1;
        case 'B': return 2;
        default: return -1;
        }
    }
    void update(int &a, int b)
    {
        if (a<0) a = b;
        else if (b>=0) a = min(a,b);
    }
    bool valid(int a[], int l, int r, int c)
    {
        for(int i=l; i<r; ++i) {
            if (a[i] >=0 && a[i] != c)
                return false;
        }
        return true;
    }
    int getMinimumCost(string desiredColor, int stampCost, int pushCost) 
    { 
        int dp[60][3];
        int goal[60];
        int n = desiredColor.size();
        for(int i=0; i<n; ++i)
            goal[i] = getid(desiredColor[i]);

        int ans=-1;
        for(int s=1; s<=n; ++s) {
            memset(dp, -1, sizeof dp);
            for(int c=0; c<3; ++c) {
                dp[0][c] = 0;
            }
            for(int p=s; p<=n; ++p) 
            for(int c=0; c<3; ++c)
            if (valid(goal, p-s, p, c))
            {
                for(int c2=0; c2<3; ++c2)
                    if (dp[p-s][c2]>=0)
                        update(dp[p][c], dp[p-s][c2]+pushCost);
                for(int i=p-s+1; i<p; ++i)
                    if (dp[i][c]>=0)
                        update(dp[p][c], dp[i][c]+pushCost);
            }
            for(int c=0; c<3; ++c) if (dp[n][c]>=0) {
                dp[n][c] += s*stampCost;
                update(ans, dp[n][c]);
            }
        }
        return ans;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "RRGGBB"; int Arg1 = 1; int Arg2 = 1; int Arg3 = 5; verify_case(0, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "R**GB*"; int Arg1 = 1; int Arg2 = 1; int Arg3 = 5; verify_case(1, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "BRRB"; int Arg1 = 2; int Arg2 = 7; int Arg3 = 30; verify_case(2, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "R*RR*GG"; int Arg1 = 10; int Arg2 = 58; int Arg3 = 204; verify_case(3, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "*B**B**B*BB*G*BBB**B**B*"; int Arg1 = 5; int Arg2 = 2; int Arg3 = 33; verify_case(4, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "*R*RG*G*GR*RGG*G*GGR***RR*GG"; int Arg1 = 7; int Arg2 = 1; int Arg3 = 30; verify_case(5, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main()
{
    Stamp __test; 
    __test.run_test(-1); 
} 
// END CUT HERE 
