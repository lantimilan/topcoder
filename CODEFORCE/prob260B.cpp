// year 2013 to 2015
// month 1 to 12
// day 1 to 28/30/31
//
// dd-mm-yyyy

#include <cctype>
#include <iostream>
#include <string>
#include <map>
using namespace std;

map<string, int> mp;

int main()
{
    string format="dd-mm-yyyy";
    string line;
    getline(cin, line);
    mp.clear();
    int n = line.length(), l = format.length();
    for (int i=0; i+l<=n; ++i) {
        string sub = line.substr(i, l);
        if (!(isdigit(sub[0]) && isdigit(sub[1]))) continue;
        if (!(sub[2] == '-')) continue;
        if (!(isdigit(sub[3]) && isdigit(sub[4]))) continue;
        if (!(sub[5] == '-')) continue;
        if (!(isdigit(sub[6]) && isdigit(sub[7]) && isdigit(sub[8]) && isdigit(sub[9]))) continue;
        int d = (sub[0]-'0')*10 + (sub[1]-'0');
        int m = (sub[3]-'0')*10 + (sub[4]-'0');
        int y = (sub[6]-'0')*1000 + (sub[7]-'0')*100 + (sub[8]-'0')*10 + (sub[9]-'0');
        if (!(2013 <= y && y<=2015)) continue;
        if (!(1 <= m && m <= 12)) continue;
        int daysinmonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (!(1 <= d && d <= daysinmonth[m])) continue;
        mp[sub]++;
    }
    map<string, int>::const_iterator cit;
    string ans;
    int best = 0;
    for (cit = mp.begin(); cit != mp.end(); ++cit) {
        if (cit->second > best) {
            best = cit->second;
            ans = cit->first;
        }
    }
    cout << ans << endl;
}
