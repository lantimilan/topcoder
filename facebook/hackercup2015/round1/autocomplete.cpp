// autocomplete.cpp
#include <iostream>
#include <string>
using namespace std;

struct Node {
    Node *child[26];
    string word;
    Node() {
        for (int i = 0; i < 26; ++i) child[i] = NULL;
        word = "";
    }
};

struct Trie {
    Node *root;
    int add(string word);
    void print() { print(root); }
    void print(Node *node);
    Trie() { root = new Node(); }
};

int Trie::add(string word) {
    int ans = 0;
    int n = word.length();
    Node *curr = root;
    for (int pos = 0; pos < n; ++pos) {
        char ch = word[pos];
        int x = ch - 'a';
        if (curr->child[x] == NULL) {
            curr->child[x] = new Node();
        } else {
            ans++;
        }
        curr = curr->child[x];
        if (pos == n-1) curr->word = word;
    }
    ans = min(ans+1, n);
    //cout << "Trie::add " << word << ' ' << ans << endl;
    return ans;
}

void Trie::print(Node* curr) {
    if (curr == NULL) return;
    cout << curr << "#" << curr->word << ": ";
    for (int i = 0; i < 26; ++i) if (curr->child[i] != NULL) {
        cout << "(" << char(i + 'a') << "," << curr->child[i] << ")";
        cout << " ";
    }
    cout << endl;
    for (int i = 0; i < 26; ++i) {
        print(curr->child[i]);
    }
}

void solve(int tcase) {
    Trie *trie = new Trie();
    int ans = 0;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        string word; cin >> word;
        int cost = trie->add(word); //cout << word << ' ' << cost << endl;
        ans += cost;
    }
    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) solve(t);
    /*
    Trie *trie = new Trie();
    trie->add("hi");
    trie->add("hello");
    trie->add("lol");
    trie->add("hills");
    trie->add("hill");
    trie->add("aaaaa");
    trie->add("aaaa");
    trie->add("aaa");
    trie->add("aa");
    trie->add("a");
    trie->print();
    */
}
