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
map<int, set<int>> tag_dests;
queue<pair<set<int>,set<int>>> que;
map<set<int>, set<int>> groups;  // tag_set => dest_set

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
        //dest_tags[dest2id[dest]].insert(tag2id[tag]);
        tag_dests[tag2id[tag]].insert(dest2id[dest]);
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
    string line;
    while (getline(cin, line)) {
        //cout << line << endl;
        parse(line);
    }
    int T = tag_dests.size();
    //cout << "input done: " << L << endl;
    for (auto &p : tag_dests) {
        set<int> st; st.insert(p.first);
        que.push(make_pair(st, p.second));
    }
    //cout << "processing done" << endl;;

    while (!que.empty()) {
        pair<set<int>,set<int>> p = que.front(); que.pop();
        set<int> tags = p.first;
        set<int> dests = p.second;
        for (int t = 0; t < T; ++t) if (!tags.count(t)) {
            if (is_subset(dests, tag_dests[t])) {
                p.first.insert(t);
                que.push(p);
            } else {
                group[p.first] = p.second;
                set<int> inter = intersect(tag_dests[t], dests);
                if (!inter.empty()) {
                    p.first.insert(t); p.second = inter;
                    que.push(p);
                }
                groups.
            }
        }
    }

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
