#include <cctype>
#include <iostream>
#include <string>
using namespace std;

void solve()
{
    string s; getline(cin, s); //cout << s << endl;

    string ans;
    int i;
    for(i=0; i < int(s.size()); )
    { 
        if (s[i]=='.') { ans += "..."; i+=3; } 
        break;
    }

    int n = s.size();
    for(; i < n; )
    {
        if (s[i] == ',') { ans += ','; if (i<n-1) ans += ' '; ++i; }
        else if (s[i] == '.') { if (ans[ans.size()-1]!=' ') ans += ' '; ans += "..."; i+=3; }
        else if (isdigit(s[i]))
        {
            for(;i<n && isdigit(s[i]); ++i) { ans+=s[i]; }
            int j;
            for(j=i; j<n && s[j]==' '; ++j); 
            if (j<n && isdigit(s[j])) ans+=' ';
        }
        else ++i;
    }
    cout << ans << endl;
}

int main()
{
    solve();
}
