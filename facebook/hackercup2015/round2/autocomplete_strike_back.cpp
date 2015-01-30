// autocomplete_strike_back.cpp
//
// 1. build trie
// 2. dp on trie, and knapsack on subtree
//
// segfault on case #17, very long words

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int INF = 20000+5;  // total number of letters for all words is 20000
int N, K;

struct Node {
    bool isWord;
    Node *child[26];
    int cost[105];
    int depth;

    Node() {
        isWord = false;
        memset(child, 0, sizeof child);
        memset(cost, 0, sizeof cost);
        depth = 0;
    }
};

int dp[30][105];  // (child, nwords)

void cleanup(Node *root)
{
    if (!root) return;
    for (int c = 0; c < 26; ++c) cleanup(root->child[c]);
    delete root;
}

Node* add_word(Node *root, const string& word)
{
    int l = word.length();
    Node *parent = root;
    for (int i = 0; i < l; ++i) {
        char ch = word[i];
        Node *next = parent->child[ch-'a'];
        if (next) {
            parent = next;
        } else {
            next = new Node();
            next->depth = parent->depth + 1;
            parent->child[ch-'a'] = next;
            parent = next;
        }
        if (i == l-1) parent->isWord = true;
    }
    return parent;
}

void chmin(int &a, int b)
{
    if (a > b) a = b;
}

int go(Node *root)
{
    if (root == NULL) return 0;

    assert(root != NULL);
    for (int c = 0; c < 26; ++c) go(root->child[c]);

    // sum children
    // dp[][] must be declared globally or otherwise each stack frame has 3000
    // integers, and we have a stack depth possibly 20000, stack overflow is real
    for (int i = 0; i < 30; ++i) for (int j = 0; j < 105; ++j) dp[i][j] = INF;
    dp[0][0] = 0;
    for (int c = 1; c <= 26; ++c) {
        dp[c][0] = 0;
        for (int k1 = 1; k1 <= K; ++k1) {
            dp[c][k1] = dp[c-1][k1]; assert(k1 < 105);
            if (root->child[c-1]) for (int k2 = 0; k2 <= k1; ++k2) {
                assert(k1 >= k2);
                int newcost = dp[c-1][k2] + root->child[c-1]->cost[k1-k2];
                chmin(dp[c][k1], newcost);
            }
        }
    }
    root->cost[0] = 0;
    if (root->depth > 0) root->cost[1] = root->depth;
    else root->cost[1] = dp[26][1];
    for (int k = 2; k <= K; ++k) {
        root->cost[k] = dp[26][k];
        if (root->isWord) {
            chmin(root->cost[k], dp[26][k-1] + root->depth);
        }
    }
    return root->cost[K];
}

void solve(int tcase)
{
    cin >> N >> K; //cout << N << ' ' << K << endl;
    Node *root = new Node();
    for (int i = 0; i < N; ++i) {
        string word; cin >> word;
        add_word(root, word);
    }

    int ans = go(root);
    cleanup(root);
    cout << "Case #" << tcase << ": ";
    // output sol
    cout << ans;
    cout << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
