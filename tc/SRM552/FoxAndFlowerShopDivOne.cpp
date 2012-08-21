// SRM 552 div 1
// p500
//
// cntL[i][j] is #L in flowers[0..i-1][0..j-1], think of it as 1-based
// the for-loop s=2 to M does split into two horizontal regions
// 1..s-1 and s..M
// and we look for rect from (x1,y1) to (x2,y2) with x2,y2 inclusive and (x1,y1)
// exclusive
//
// for grid problem with tricky index
// draw a picture and figure out index before typing
//
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

int cntL[40][40];
int cntP[40][40];
int dp1[2000], dp2[2000];

class FoxAndFlowerShopDivOne
{ 
public: 
    void chmax(int &a, int b)
    {
        a = (a>b)?a:b;
    }
    int solve(vector<string> flowers, int maxDiff)
    {
        memset(cntL, 0, sizeof cntL);
        memset(cntP, 0, sizeof cntP);
        int M = flowers.size();
        int N = flowers[0].size();
        for(int i=1; i<=M; ++i)
        for(int j=1; j<=N; ++j) {
            cntL[i][j] = cntL[i-1][j] + cntL[i][j-1] - cntL[i-1][j-1] + (flowers[i-1][j-1]=='L');
            cntP[i][j] = cntP[i-1][j] + cntP[i][j-1] - cntP[i-1][j-1] + (flowers[i-1][j-1]=='P');
        }

        int ans=-1;
        for(int s=2; s<=M; ++s)
        {
        memset(dp1, -1, sizeof dp1);
        memset(dp2, -1, sizeof dp2);
        for(int x1=0; x1<s; ++x1)
        for(int y1=0; y1<=N; ++y1)
        for(int x2=x1+1; x2<s; ++x2)
        for(int y2=y1+1; y2<=N; ++y2)
        {
            int numL, numP;
            numL = cntL[x2][y2] - cntL[x1][y2] - cntL[x2][y1] + cntL[x1][y1];
            numP = cntP[x2][y2] - cntP[x1][y2] - cntP[x2][y1] + cntP[x1][y1];
            chmax(dp1[numL-numP+1000], numL + numP);
        }
        for(int x1=s-1; x1<M; ++x1)
        for(int y1=0; y1<=N; ++y1)
        for(int x2=x1+1; x2<=M; ++x2)
        for(int y2=y1+1; y2<=N; ++y2)
        {
            int numL, numP;
            numL = cntL[x2][y2] - cntL[x1][y2] - cntL[x2][y1] + cntL[x1][y1];
            numP = cntP[x2][y2] - cntP[x1][y2] - cntP[x2][y1] + cntP[x1][y1];
            chmax(dp2[numL-numP+1000], numL + numP);
        }
        for(int d1=0; d1<2000; d1++)
        for(int d2=0; d2<2000; d2++)
        if (abs(d1-1000 + d2-1000) <= maxDiff)
        if (dp1[d1]>=0 && dp2[d2]>=0)
        {
            chmax(ans, dp1[d1] + dp2[d2]);
        }
        }
        return ans;
    }

    int theMaxFlowers(vector <string> flowers, int maxDiff) 
    { 
        int ans;
        ans = solve(flowers, maxDiff);
        int M = flowers.size();
        int N = flowers[0].size();
        vector<string> flip(N, string(M,' '));
        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            flip[j][i] = flowers[i][j];
        flowers = flip;
        ans = max(ans, solve(flowers, maxDiff));
        return ans;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"LLL",
 "PPP",
 "LLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 7; verify_case(0, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"LLL",
 "PPP",
 "LLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 6; verify_case(1, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"...",
 "...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 0; verify_case(2, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"LLPL.LPP",
 "PLPPPPLL",
 "L.P.PLLL",
 "LPL.PP.L",
 ".LLL.P.L",
 "PPLP..PL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 38; verify_case(3, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = -1; verify_case(4, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"LLLP..LLP.PLL.LL..LP",
 "L.PL.L.LLLL.LPLLPLP.",
 "PLL.LL.LLL..PL...L..",
 ".LPPP.PPPLLLLPLP..PP",
 "LP.P.PPL.L...P.L.LLL",
 "L..LPLPP.PP...PPPL..",
 "PP.PLLL.LL...LP..LP.",
 "PL...P.PPPL..PLP.L..",
 "P.PPPLPLP.LL.L.LLLPL",
 "PLLPLLP.LLL.P..P.LPL",
 "..LLLPLPPPLP.P.LP.LL",
 "..LP..L..LLPPP.LL.LP",
 "LPLL.PLLPPLP...LL..P",
 "LL.....PLL.PLL.P....",
 "LLL...LPPPPL.PL...PP",
 ".PLPLLLLP.LPP...L...",
 "LL...L.LL.LLLPLPPPP.",
 "PLPLLLL..LP.LLPLLLL.",
 "PP.PLL..L..LLLPPL..P",
 ".LLPL.P.PP.P.L.PLPLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; int Arg2 = 208; verify_case(5, Arg2, theMaxFlowers(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main()
{
    FoxAndFlowerShopDivOne __test; 
    __test.run_test(-1); 
} 
// END CUT HERE 
