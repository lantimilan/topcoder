#include <iostream>
#include <stack>
#include <string>
using namespace std;

void solve()
{
    string s; cin >> s;
    stack<int> past;
    int n=s.size();
    for(int i=0; i<n-1; ++i)
    {
        if (s[i] == s[i+1])
        {
            s[i] = s[i+1] = 'X';
            int p=i-1, q=i+2;
            while(p>=0 && q<n)
            {
                if (s[p] == 'X')
                {
                    if (!past.empty())
                    { p = past.top(); past.pop(); }
                    else break;
                }
                if (s[p] != s[q]) break;
                s[p] = s[q] = 'X'; p--; q++;
            }
            if (p>=0 && s[p] != 'X') past.push(p);
        }
    }
    string ans;
    for(int i=0; i<n; ++i)
        if (s[i] != 'X') ans += s[i];
    cout << ans << endl;
}
int main()
{
    solve();
}
