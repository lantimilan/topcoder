#include <iostream>
#include <string>
using namespace std;

void solve()
{
    string num; cin >> num;
    int n = num.size();
    if (n==1) { cout << 0 << endl; return; }
    int cnt=1;
    int k=0;
    for(int i=0; i<n; ++i) k += num[i]-'0';
    while(k/10) {
        ++cnt;
        int kk=0;
        for(; k; k/=10) kk+=k%10;
        k = kk;
    }
    cout << cnt << endl;
}

int main()
{
    solve();
}
