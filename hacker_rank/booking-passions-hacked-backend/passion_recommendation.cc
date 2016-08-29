///////////////////////////////////////////////////////////////////////////
// passion_recommendation.cc
/////////////////////////////
//
// A travel destination recommendation system.
//
// Database is a list of cities with passion and endorsement count.
// Query is user's list of passions.
// Return a list of recommended destinations to travel.
//
// Major data structure, dict, is a collection of city to passion to
// endorsement mapping. This is a conscious decision. Reasons are:
// 1. Cities are relatively stable set and does not change frequently.
// 2. When scalability is a concern, we could have multiple servers and
// each server is responsible on a subset of cities.
// 3. User might have a number of passions but this number is usually
// small, probably around 10 for a common user, and this would make looping
// through all passions not that expensive.
//
// Questions presented in problem statement:
// + User might have multiple passions.
// Answer: We might want to consider only the top 3 or top 5 passions, and
// we could give different weight to different positions when comes to
// score a city.
// Moreover, we should only output 5 to 10 destinations, each with a brief
// description of the highlight of that city. Having 100 or even more
// recommendations rarely makes sense and very few users would actually
// taking destinations ranked 50 or 60 seriously.
// + Popular cities might have a high count of endorsement, do we need to
// adjust weight according to popularity?
// Answer: Use the median of a city's top 5 endorsement as a popularity
// indicator and scale a city's score on a passion proportionally.
// + Filter out jokes like London is good for shark diving.
// Answer: This requires some domain knowledge and special rules. Probably
// just filter out those joke passions.
//
// Step 1: Do something simple and get a model/predictor off ground quickly.
///////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

namespace {

// TODO: These should be command line flags.
const char INPUT[] = "passion_hacked.in";
const char PROMPT[] = "> ";
const int NUM_PASSIONS = 3;  // Consider only the first three passions.
const int NUM_DESTINATIONS = 2;  // Recommend at most 2 cities.

map<string, map<string, int>> dict;  // city => (passion, weight)

struct ScoreEntry {
    string city;
    int score;
    ScoreEntry(string cc, int ss) : city(cc), score(ss) {}
};
bool operator<(const ScoreEntry &s1, const ScoreEntry &s2) {
    if (s1.score != s2.score) {
        return s1.score > s2.score;
    }
    return s1.city > s2.city;
}

vector<string> split(const string &line, char delim) {
    int n = line.length();
    int start, end;
    vector<string> vec;
    for (start = 0; start < n; start = end+1) {
        for (end = start+1; end < n && line[end] != delim; ++end) { }
        vec.push_back(line.substr(start, end-start));
    }
    return vec;
}

int str2int(const string &s) {
    int num = 0;
    for (int i = 0; i < s.length(); ++i) {
        num = num * 10 + s[i] - '0';
    }
    return num;
}

void init() {
    dict.clear();
    ifstream fin(INPUT);
    string line;
    while (getline(fin, line)) {
        vector<string> vec = split(line, ',');
        assert(vec.size() == 3);
        string city = vec[0];
        string passion = vec[1];
        int score = str2int(vec[2]);
        dict[city][passion] = score;
    }
}

vector<string> get_passions(const string &query) {
    vector<string> passions_in_query = split(query, ',');
    vector<string> passions;
    for (int i = 0; i < passions_in_query.size(); ++i) {
        if (i >= NUM_PASSIONS) {
            break;
        }
        passions.push_back(passions_in_query[i]);
    }
    return passions;
}

vector<string> get_cities(const vector<string>& passions) {
    map<string, int> scores;
    for (const string& passion : passions) {
        for (const auto &city : dict) {
            const string &city_name = city.first;
            const auto &known = city.second;
            if (known.count(passion)) {
                scores[city_name] += known.find(passion)->second;
            }
        }
    }

    priority_queue<ScoreEntry> destinations;
    for (const auto &p : scores) {
        string city = p.first;
        int score = p.second;
        destinations.push(ScoreEntry(city, score));
        if (destinations.size() > NUM_DESTINATIONS) {
            destinations.pop();
        }
    }

    vector<string> city_list;
    while (!destinations.empty()) {
        city_list.push_back(destinations.top().city);
        destinations.pop();
    }
    reverse(city_list.begin(), city_list.end());
    return city_list;
}

}  // unnamed namespace

int main() {
    init();

    cout << "Welcome to travel recommendation system.\n";
    cout << "Type a list of passions separated by comma.\n"
         << "Example: Hiking,Surfing\n";
    cout << "Type Ctrl-D, or quit or q or Q to quit.\n";

    while (true) {
        cout << PROMPT;
        string query;
        getline(cin, query);
        if (query.empty() || tolower(query[0]) == 'q') {
            cout << "Bye!\n";
            break;
        }

        vector<string> passions = get_passions(query);
        vector<string> destinations = get_cities(passions);

        if (destinations.empty()) {
            cout << "We were unable to find destinations that match your"
                    " passions, please use some different passions and try"
                    " again." << endl;
        } else {
            cout << "Most recommended destinations:\n";
            for (const string &dest : destinations) {
                cout << dest << endl;
            }
        }
    }
}

