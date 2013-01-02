// easy implementation problem
// is cin/cout faster enough?
//
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<string,int> mp;
map<string, string> chefmap;
map<string, int> country_score;
vector<string> chefs;
vector<string> states;

int main()
{
    mp.clear(); chefmap.clear();
    chefs.clear(); states.clear();

    int N, M; cin >> N >> M;
    for (int i=0; i<N; ++i) {
        string name, country;
        cin >> name >> country;
        chefmap[name] = country;
    }
    for (int i=0; i<M; ++i) {
        string email; cin >> email;
        mp[email]++;
    }
    int best = 0;
    map<string,int>::const_iterator it;
    for (it = mp.begin(); it != mp.end(); ++it) {
        string name = it->first;
        int vote = it->second;
        string country = chefmap[name];
        country_score[country] += vote;
        if (vote > best) {
            best = vote;
            chefs.clear(); chefs.push_back(name);
        } else if (vote == best) {
            chefs.push_back(name);
        }
    }
    int country_best = 0;
    for (it = country_score.begin(); it != country_score.end(); ++it) {
        string country = it->first;
        int score = it->second;
        if (score > country_best) {
            country_best = score;
            states.clear(); states.push_back(country);
        } else if (score == country_best) {
            states.push_back(country);
        }
    }
    sort(chefs.begin(), chefs.end());
    sort(states.begin(), states.end());
    cout << states[0] << endl;
    cout << chefs[0] << endl;
}

// Correct Answer
// Execution Time: 2.11
