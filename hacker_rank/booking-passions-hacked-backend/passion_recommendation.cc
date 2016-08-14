// passion_recommendation.cc
//
// Database is a list of cities with passion and endorsement count.
// Query is user's list of passions.
// Return a list of recommended destinations to travel.
//
// + User might have multiple passions, shall we give different weight to
// different position?
// + Popular cities might have a high count of endorsement, do we need to
// adjust weight according to popularity? Maybe use city's population as
// an indicator?
// + Filter out jokes like London is good for shark diving.
//
// step 1: Do something simple and get a model/predictor off ground quickly.
//
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int NUM_PASSIONS = 3;  // Consider only the first three passions.
const int NUM_DESTINATIONS = 2;  // Recommend at most 2 cities.

map<string, vector<pair<string, int>>> dict;  // city => (passion, weight)

const char prompt[] = "> ";

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

void init(const string &filename) {
    dict.clear();
    ifstream fin(filename.c_str());
    string line;
    while (getline(fin, line)) {
        vector<string> vec = split(line, ',');
        assert(vec.size() == 3);
        string city = vec[0];
        string passion = vec[1];
        int score = str2int(vec[2]);
        dict[city].push_back(make_pair(passion, score));
    }
    for (const auto &p : dict) {
        cout << p.first << ": ";
        for (const auto &v : p.second) {
            cout << v.first << ", ";
        }
        cout << endl;
    }
}

bool contains(const vector<string> &vec, const string &s) {
    for (const string k : vec) {
        if (k == s) return true;
    }
    return false;
}

int main() {
    const char input[] = "passion_hacked.in";
    init(input);

    cout << "Welcome to travel recommendation system.\n";
    cout << "Type a list of passions separated by comma.\n";
    cout << "Type quit or q or Q to quit.\n";
    while (true) {
        cout << prompt;
        string query;
        getline(cin, query);
        if (query.empty() || tolower(query[0]) == 'q') {
            cout << "Bye!\n";
            break;
        }

        vector<string> passions = split(query, ',');

        map<string, int> scores;
        for (const string& passion : passions) {
            for (const auto &city : dict) {
                for (const auto &known : city.second) {
                    const string city_name = city.first;
                    if (contains(passions, known.first)) {
                        scores[city_name] += known.second;
                    }
                }
            }
        }

        int best_score = -1;
        string best_city;
        for (const auto &p : scores) {
            if (p.second > best_score) {
                best_score = p.second;
                best_city = p.first;
            }
        }
        cout << "Most recommended: " << best_city << endl;
    }
}

