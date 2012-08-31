/////////////////////////////////////////////
// http://codeforces.com/contest/105/problem/B
//
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

bool incr(vector<int> &vec, int k)
{
    int carry=1;
    for(size_t i=0; i<vec.size(); ++i)
    {
        vec[i]+=carry;
        if (vec[i]>k) { carry = 1; vec[i]=0; }
        else carry=0;
    }
    if (carry) return false;
    else return true;
}

double calc(const vector<int> &prob, const vector<int> &level, int pos, int cum, int A, int B)
{
    int n = prob.size();
    if (pos>=n) {
        if (cum > n/2) return 1.0; 
        else return A*1.0/(A+B);
    }
    double p = prob[pos]*1.0/100;
    return p*calc(prob,level,pos+1,cum+1,A,B) + 
        (1.0-p)*calc(prob,level,pos+1,cum,A,B+level[pos]);
}

void solve()
{
    int n,k,A; cin >> n >> k >> A;
    vector<int> level(n), loyal(n);
    for(int i=0; i<n; ++i) cin >> level[i] >> loyal[i];

    double ans=0;
    vector<int> candies(n,0);
    do {
        int sum=0;
        for(size_t i=0; i<candies.size(); ++i) sum+=candies[i];
        if (sum>k) continue;
        // calc prob
        vector<int> prob(n);
        for(int i=0; i<n; ++i) prob[i] = min(100,loyal[i]+10*candies[i]);
        ans = max(ans, calc(prob,level,0,0,A,0));
    } while(incr(candies,k)); 
    cout << fixed << setprecision(10) << ans << endl;
}

int main()
{
    solve();
}
