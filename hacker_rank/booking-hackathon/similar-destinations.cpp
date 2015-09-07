// similar-destinations.cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

int N;
int DESTID = 0;
int TAGID = 0;
map<string, int> dest2id;
map<int, string> id2dest;
map<string, int> tag2id;
map<int, string> id2tag;
map<int, set<int>> dest_tags;
map<set<int>, set<int>> groups;

void parse(string &line) {
    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == ':' || line[i] == ',') line[i] = ' ';
    }
    istringstream iss(line);
    string dest; iss >> dest;
    dest2id[dest] = DESTID; id2dest[DESTID] = dest; DESTID++;
    string tag;
    while (iss >> tag) {
        if (!tag2id.count(tag)) {
            tag2id[tag] = TAGID; id2tag[TAGID] = tag; TAGID++;
        }
        dest_tags[dest2id[dest]].insert(tag2id[tag]);
    }
}

string construct(const set<int> &ids, const map<int, string> &tbl) {
    vector<string> vec;
    for (int id : ids) {
        vec.push_back(tbl.at(id));
    }
    sort(vec.begin(), vec.end());

    string ans;
    for (int i = 0; i < vec.size(); ++i) {
        if (i) ans += ",";
        ans += vec[i];
    }
    return ans;
}

int main() {
    cin >> N; cin.ignore();
    int L = 0;
    string line;
    while (getline(cin, line)) {
        //cout << line << endl;
        parse(line);
        ++L;
    }
    //cout << "input done: " << L << endl;
    for (int i = 0; i < L; ++i)
    for (int j = i+1; j < L; ++j) {
        set<int> common;
        for (int tagid : dest_tags[i]) if (dest_tags[j].count(tagid)) {
            common.insert(tagid);
        }
        groups[common].insert(i);
        groups[common].insert(j);
    }
    //cout << "processing done" << endl;;

    vector<pair<int,string>> ans;
    for (auto &p : groups) if (p.first.size() >= N) {
        set<int> tags = p.first;
        set<int> dests = p.second;
        string s1 = construct(dests, id2dest);
        string s2 = construct(tags, id2tag);
        //cout << s1 << ":" << s2 << endl;
        ans.push_back(make_pair(-tags.size(), s1+":"+s2));
    }
    sort(ans.begin(), ans.end());
    for (auto &p : ans) {
        cout << p.second << endl;
    }
}
